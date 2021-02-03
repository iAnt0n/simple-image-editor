CFLAGS=--std=c18 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc

all: img_edit

bmp.o: formats/bmp.c
	$(CC) -c $(CFLAGS) $< -o $@

image.o: image.c
	$(CC) -c $(CFLAGS) $< -o $@

util.o: util.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

io.o: io.c
	$(CC) -c $(CFLAGS) $< -o $@

rotate.o: actions/rotate.c
	$(CC) -c $(CFLAGS) $< -o $@

black_and_white.o: actions/black_and_white.c
	$(CC) -c $(CFLAGS) $< -o $@

img_edit: image.o main.o util.o bmp.o io.o rotate.o black_and_white.o
	$(CC) -o img_edit $^

clean:
	rm -f *.o img_edit
