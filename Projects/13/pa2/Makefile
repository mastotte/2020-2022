CC = clang

CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: hw2

hw2: num_arrays.o hw2.o
	$(CC) num_arrays.o hw2.o -o hw2

num_arrays.o: num_arrays.c num_arrays.h
	$(CC) $(CFLAGS) -c num_arrays.c

hw2.o: hw2.c num_arrays.h
	$(CC) $(CFLAGS) -c hw2.c

clean:
	rm -f hw2 hw2.o num_arrays.o

format:
	clang-format -i -style=file *.{c,h}
