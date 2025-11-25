#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define TO_RAD(deg) ((float)deg * (M_PI / 180.0f))
#define TO_DEG(rad) ((int)(rad * (180.0f / M_PI)))

typedef struct {
    int x;
    int y;
    int xVel;
    int yVel;
    int screenX;
    int screenY;
    int angle;
} Car;

void handle_input(bool inputs[6]) {
    char input = '1';
    input = getch();
    if (input == 'w') {
	inputs[0] = true;
    } else {
	inputs[0] = false;
    }
    if (input == 'a') {
	inputs[1] = true;
    } else {
	inputs[1] = false;
    }
    if (input == 's') {
	inputs[2] = true;
    } else {
	inputs[2] = false;
    }
    if (input == 'd') {
	inputs[3] = true;
    } else {
	inputs[3] = false;
    }
    if (input == 'q') {
	inputs[4] = true;
    } else {
	inputs[4] = false;
    }
    if (input == 'e') {
	inputs[5] = true;
    } else {
	inputs[5] = false;
    }
}

void draw_screen(struct winsize *win, Car* car) {
    clear();
    int screenX = win->ws_col * ((float) car->screenX / 512);
    int screenY = win->ws_row * ((float) car->screenY / 288);
    wmove(stdscr, screenY, screenX);
    printw("#");
    wmove(stdscr, 10, 0);
    printw("%d", car->screenX);
    wmove(stdscr, 11, 0);
    printw("%d", car->screenY);
    refresh();
}

void move_player(Car* car, bool inputs[6]) {
    if (inputs[0]) {
	car->y -= 5 * cos(TO_RAD(car->angle));
	car->x += 5 * sin(TO_RAD(car->angle));
	car->screenY -= 5 * cos(TO_RAD(car->angle));
	car->screenX += 5 * sin(TO_RAD(car->angle));
    }
    if (inputs[1]) {
	car->y -= 5 * sin(TO_RAD(car->angle));
	car->x -= 5 * cos(TO_RAD(car->angle));
	car->screenY -= 5 * sin(TO_RAD(car->angle));
	car->screenX -= 5 * cos(TO_RAD(car->angle));
    }
    if (inputs[2]) {
	car->y += 5 * cos(TO_RAD(car->angle));
	car->x -= 5 * sin(TO_RAD(car->angle));
	car->screenY += 5 * cos(TO_RAD(car->angle));
	car->screenX -= 5 * sin(TO_RAD(car->angle));
    }
    if (inputs[3]) {
	car->y += 5 * sin(TO_RAD(car->angle));
	car->x += 5 * cos(TO_RAD(car->angle));
	car->screenY += 5 * sin(TO_RAD(car->angle));
	car->screenX += 5 * cos(TO_RAD(car->angle));
    }
    if (inputs[4]) {
	car->angle -= 30;
	if (car->angle < -180) {
	    car->angle += 360;
	}
    }
    if (inputs[5]) {
	car->angle += 30;
	if (car->angle > 180) {
	    car->angle -= 360;
	}
    }
}


int main(void) {
    bool inputs[6] = {false};
    char letter;

    initscr();
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    nodelay(stdscr, true);

    int screenWidth = w.ws_col;
    int screenHeight = w.ws_row;

    Car car = {.x = 0, .y = 0, .xVel = 0, .yVel = 0, .screenX = 0, .screenY = 0, .angle = 0};
    
    printw("Press");
    wmove(stdscr, 0, 0);
    printw("row is %d, col is %d", w.ws_row, w.ws_col);
    refresh();

    letter = getch();
    clear();
    printw("letter is %d or %c", letter, letter);
    curs_set(0);
    refresh();
    srand(time(NULL));

    for (;;) {
	handle_input(inputs);
	move_player(&car, inputs);
	draw_screen(&w, &car);
	usleep(48000);
    }

    nodelay(stdscr, false);
    wmove(stdscr, 0, 0);
    printw("YOU LOSE, YOUR FINAL SCORE WAS.");
    getch();

    endwin();

    return 0;
}
