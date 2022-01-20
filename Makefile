CC=gcc
SRC= main.c carte.c joueur.c action.c
OBJ=$(SRC:.c=.o)
FLAGS=-Wall

uno:    $(OBJ) uno.h
	$(CC) -o $@ $(OBJ)
%.o:	%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o *~ core