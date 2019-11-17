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
	touch "text.txt"
	touch "test.txt"
	mkdir "makeDir/"
	touch "makeDir/file.txt"
	./program
clean:
	rm *.o
	rm *.txt
	rm -rf "makeDir/"
	rm program
