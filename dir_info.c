#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv){
  printf("\nWelcome to Alma's DIR_INFO\n");
  printf("If you'd like to scan a different directory, do ./program (path)\n");
  DIR *path = NULL;
  struct dirent *current = NULL;

  if (argc > 1){
    path = opendir(argv[1]);
    printf("Reading through directory: %s\n", argv[1]);
    if (errno != 0){
      printf("LINE 16 errno: %d\tstrerror:%s\n", errno, strerror(errno));
    }
  }else{
    printf("NO ARGUMENT! Quitting\n");
    return 0;
  }
  //printing out the files and directories
  int size = 0;
  //going thru all files, if it's a file mark it as such and if not mark it as f
  //add up size if it's a file
  //print out size at end
  errno = 0;
  current = readdir(path);
  if (errno != 0){
    printf("LINE 30 errno: %d\tstrerror:%s\n", errno, strerror(errno));
  }
  printf("\n");
  char fullpath[256];
  while (current != NULL){
    if (current->d_type == DT_REG){
      //size
      struct stat buffer;
      //setting pathname so it works for files not in cwd
      fullpath[0] = '\0';
      strcpy(fullpath, argv[1]);
      //printf("pathname: %s\n", fullpath);
      //printf("argv[1]: %s\n", argv[1]);
      strcat(fullpath, "/");
      //printf("line42 pathname: %s\n", fullpath);
      strcat(fullpath, current->d_name);
      //printf("pathname: %s\n", fullpath);
      stat(fullpath, &buffer);
      //printf("just about to take size, name of current: %s\n", current->d_name);

      size += buffer.st_size; //adding the size
      //print out
      if (errno != 0){
        printf("LINE 43 (SIZE) errno: %d\tstrerror:%s\n", errno, strerror(errno));
      }
      printf("f: %s\n", current->d_name);
    }else if(current->d_type == DT_DIR){
      printf("d: %s\n", current->d_name);
    }
    errno = 0;
    current = readdir(path);//increment
    //printf("current: %s\n", current->d_name);
    if (errno != 0){
      printf("LINE 53 errno: %d\tstrerror:%s\n", errno, strerror(errno));
    }
  }
  printf("total size: %d BYTES\n", size);
  printf("thanks for looking!\n");
  printf("\n");
  return 0;
}
