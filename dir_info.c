#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int print_files(DIR *current);
int print_directories(DIR *current);
int size_of_directory(DIR *current);

int main(){
  errno = 0;
  printf("\n-------\nstatistics for the current directory \".\":\n");
  DIR *current = opendir(".");
  if (errno != 0){
    printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
  }
  printf("size of directory: %d Bytes\n\n", size_of_directory(current));
  closedir(current);
  current = opendir(".");
  print_directories(current);
  //so that i can scan once more for files
  closedir(current);
  current = opendir(".");
  print_files(current);
  closedir(current);
  return 0;
}

int print_files(DIR *current){
  printf("REG FILES:\n");
  struct dirent *reading;
  reading = readdir(current);

  if (errno!=0){
    printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
  }

  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 8){
      printf("\t%s\n", reading->d_name);
    }

    reading = readdir(current);
    if (errno!=0){
      printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
    }

  }
  printf("\n");
  return 0;
}

int print_directories(DIR *current){
  printf("DIRECTORIES:\n");
  struct dirent *reading;
  reading = readdir(current);

  if (errno!=0){
    printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
  }

  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 4){
      printf("\t%s\n", reading->d_name);
    }

    reading = readdir(current);
    if (errno!=0){
      printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
    }

  }
  printf("\n");
  return 0;
}

int size_of_directory(DIR *current){
  struct dirent *reading;
  int size = 0;
  reading = readdir(current);
  if (errno!=0){
    printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
  }
  struct stat st;
  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 8){
      //printf("reading in this file: %s\n", (reading->d_name));
      stat(reading->d_name, &st);
      size+=(st.st_size);
    }
    reading = readdir(current);
    if (errno!=0){
      printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
    }
  }
  return size;
}
