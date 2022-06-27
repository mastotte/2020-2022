BASE_SOURCES   = Game.c Scoreboard.c
BASE_OBJECTS   = Game.o Scoreboard.o
HEADERS        = Game.h Scoreboard.h

CC = clang
//CFLAGS = -Wall -Wpedantic -Werror -Wextra

Client: Client.o $(BASE_OBJECTS)
	$(CC) -o Client Client.o -lm $(BASE_OBJECTS)

Client.o: Client.c $(HEADERS)
	$(CC) $(CFLAGS) -c Client.c

clean:
	rm -f Client Client.o Scoreboard.o Game.o trash:

format:
	clang-format -i -style=file *.{c,h}
