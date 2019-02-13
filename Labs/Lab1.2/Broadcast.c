#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int fd1, fd2, operms, termNum;
  char c[2];
  char filepath[200];
  char msg[200];
  mode_t permissions;

//Setup File permissions
  operms = O_CREAT | O_WRONLY;
  permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  if(argc < 2){
    printf("Invalid input. \n");
  }
  //Capturing msg
  for(int i = 1; i < argc; ++i){
    strcat(msg, argv[i]);
  }
  printf("Message sending to terminals: %s\n", msg);
  //opening fd1 file to read only
  system("ls /dev/pts/  | wc -l > count.txt");
  fd1 = open("foo.txt", O_RDONLY);
  if(fd1 < 0){
    printf("Could not open file %s\n", argv[1]);
  }
  /*
  while ( read(fd1, c, 20) != 0) {
    write(fd2, c, 20); 
  }
  */
  read(fd1, c, 2);
  //count terms open
  termNum = atoi(c) - 1;
  printf("Terminals open: %d\n", termNum);

  // Message transmiter to terms.
  for (int i = 0; i < termNum; ++i){
    sprintf(filepath, "/dev/pts/%d", i);
    fd2 = open(filepath, operms, permissions);
  }

  //closing files to liberate mem.
  close(fd1);
  close(fd2);
  return 0;
}