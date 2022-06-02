CC = clang

# Make sure to use the full CFLAGS before turning in. Uncomment this for lax
# checking during development, if you need to.
# CFLAGS =

# You can comment this out and use the above CFLAGS instead if you need to,
# during development.
CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: review_main yelling

review_main: review_main.o review.o
	$(CC) review.o review_main.o -o review_main

review_main.o: review_main.c review.h
	$(CC) $(CFLAGS) -c review_main.c

review.o: review.c review.h
	$(CC) $(CFLAGS) -c review.c

yelling: yelling.c
	$(CC) $(CFLAGS) yelling.c -o yelling

clean:
	rm -f review.o review_main.o yelling.o review_main yelling

format:
	clang-format -i -style=file *.[ch]
