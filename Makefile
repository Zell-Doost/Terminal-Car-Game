

CC=gcc

CFLAGS=-g -Wall -pedantic -std=gnu99

O=linux

LIBS= -lncurses -lm 

OBJS= 						\
			$(O)/input.o

all:	$(O)/2dCar

clean:
	rm -f *.o *~ *.flc
	rm -f linux/*

$(O)/2dCar:		$(OBJS) $(O)/main.o
	$(CC) $(OBJS) $(O)/main.o \
		-o $(O)/2dCar $(LIBS)

$(O)/%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
