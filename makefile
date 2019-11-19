ifeq ($(DEBUG), true)
CC=gcc -g
else
CC=gcc
endif

all: dir_info.o
	$(CC) -o program dir_info.o
dir_info.o:
	$(CC) -c dir_info.c
run:
	./program .
clean:
	rm *.o
	rm program
