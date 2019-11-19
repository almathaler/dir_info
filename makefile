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
	touch "text.txt" "test.txt"
	mkdir "dir1/"
	touch "dir1/file.txt"
	echo "random text to beef up size" >> "dir1/file.txt"
	mkdir "dir2/"
	touch "dir2/file.txt" "dir2/file2.txt" "dir2/file3.txt"
	echo "more random text. want this to be really long. should also add more files" >> "dir2/file.txt"
	./program
clean:
	rm *.o
	rm *.txt
	rm -rf "dir1/"
	rm -rf "dir2/"
	rm program
