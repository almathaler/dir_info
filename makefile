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
	mkdir "makeDir/"
	touch "makeDir/file.txt"
	echo "random text to beef up size" >> "makeDir/file.txt"
	mkdir "makeDir2/"
	touch "makeDir2/file.txt" "makeDir2/file2.txt" "makeDir2/file3.txt"
	echo "more random text. want this to be really long. should also add more files" >> "makeDir2/file.txt"
	./program
clean:
	rm *.o
	rm *.txt
	rm -rf "makeDir/"
	rm -rf "makeDir2/"
	rm program
