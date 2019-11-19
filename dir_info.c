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

int main(int argc, char **argv){
  errno = 0;
  char *d = NULL;
  DIR *current = NULL;
  //printf("current length of argv: %d\n", argc);
  if (argc > 1){
    d = argv[1];
  }else{
    printf("STOP! You must input a directory to scan. Quitting\n");
    return 0;
  }
  //printf("argv1: %s\n", argv[1]);
  printf("\n--------\nstatistics for the current directory \"%s\":\n", d);
  printf("if you would like to check another directory, rerun as \"./program (input)\"\n");
  current = opendir(d);
  if (errno != 0){
    printf("errno: %d\t strerror: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("\nsize of directory (of all non-directory files): %d Bytes\n", size_of_directory(current));
  closedir(current);

  current = opendir(d);
  print_directories(current);
  //so that i can scan once more for files
  closedir(current);

  current = opendir(d);
  print_files(current);
  closedir(current);
  printf("---------\n\n");
  return 0;
}

int print_files(DIR *current){
  printf("\nfiles:\n");
  struct dirent *reading;
  reading = readdir(current);

  if (errno!=0){
    printf("PRINT FILES errno: %d\t strerror: %s\n", errno, strerror(errno));
    return 0;
  }

  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 8){
      printf("\t%s\n", reading->d_name);
    }

    reading = readdir(current);
    if (errno!=0){
      printf("PRINT FILES errno: %d\t strerror: %s\n", errno, strerror(errno));
      return 0;
    }

  }
  printf("\n");
  return 0;
}

int print_directories(DIR *current){
  printf("\ndirectories:\n");
  struct dirent *reading;
  reading = readdir(current);

  if (errno!=0){
    printf("PRINT DIRECTORIES errno: %d\t strerror: %s\n", errno, strerror(errno));
    return 0;
  }

  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 4){
      printf("\t%s\n", reading->d_name);
    }

    reading = readdir(current);
    if (errno!=0){
      printf("PRINT DIRECTORIES errno: %d\t strerror: %s\n", errno, strerror(errno));
      return 0;
    }

  }
  //printf("\n");
  return 0;
}

int size_of_directory(DIR *current){
  struct dirent *reading;
  int size = 0;
  reading = readdir(current);
  if (errno!=0){
    printf("SIZE errno: %d\t strerror: %s\n", errno, strerror(errno));
    return 0;
  }
  struct stat st;
  while(reading!=NULL){
    //man dirent
    //if d_type = 4 then directory and if = 8 then 'reg', i assume just file
    if (reading->d_type == 8){
      //printf("reading in this file: %s\n", (reading->d_name));
      stat(reading->d_name, &st);
      size+=(st.st_size);
      //below is to go into directoreis
    }
    reading = readdir(current);
    if (errno!=0){
      printf("SIZE DIRECTORY errno: %d\t strerror: %s\n", errno, strerror(errno));
      return 0;
    }
  }
  return size;
}
