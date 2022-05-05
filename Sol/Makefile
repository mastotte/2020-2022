BASE_SOURCES   = Quad.c Double.c Triple.c Scoreboard.c
BASE_OBJECTS   = Quad.o Double.o Triple.o Scoreboard.o
HEADERS        = Quad.h Double.h Triple.h Scoreboard.h

CC = clang
//CFLAGS = -Wall -Wpedantic -Werror -Wextra

Client: Client.o $(BASE_OBJECTS)
	$(CC) -o Client Client.o -lm $(BASE_OBJECTS)

Client.o: Client.c $(HEADERS)
	$(CC) $(CFLAGS) -c Client.c

clean:
	rm -f Client Client.o

format:
	clang-format -i -style=file *.{c,h}
