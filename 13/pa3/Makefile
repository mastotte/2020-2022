CC = clang


CFLAGS =

CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: hw3

hw3: hw3.o stack_calculator.o
	$(CC) stack_calculator.o hw3.o -o hw3

stack_calculator.o: stack_calculator.c stack_calculator.h
	$(CC) $(CFLAGS) -c stack_calculator.c

hw3.o: hw3.c stack_calculator.h
	$(CC) $(CFLAGS) -c hw3.c

clean:
	rm -f hw3 hw3.o stack_calculator.o

format:
	clang-format -i -style=file *.{c,h}
