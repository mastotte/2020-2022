CC = clang
//CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: Game

Game: Game.o
	$(CC) -o Game Game.o -lm

Game.o: Game.c
	$(CC) $(CFLAGS) -c Game.c

clean:
	rm -f Game Game.o

format:
	clang-format -i -style=file *.{c,h}
