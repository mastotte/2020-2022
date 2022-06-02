CC = clang

# Make sure to use the full CFLAGS before turning in. Uncomment this for lax
# checking during development, if you need to.
# CFLAGS =

# You can comment this out and use the above CFLAGS instead if you need to,
# during development.
CFLAGS = -Wall -Wpedantic -Werror -Wextra


all: hw7

hw7: hw7.c
	$(CC) $(CFLAGS) hw7.c -o hw7
clean:
	rm -f hw7

format:
	clang-format -i -style=file *.[ch]
