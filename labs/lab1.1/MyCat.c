#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define Error 1

int main(int argc, char *argv[]){

    if(argc == 2){
       int fd1 = open(argv[1], O_RDONLY);
       if (fd1 < 0){
            printf("Couldn't open file:  %s\n", argv[1]);
            return Error;
       }else{
            int sz; 
            char *c = (char *) calloc(200, sizeof(char)); 
            sz = read(fd1, c, 20); 

            printf("called read(% d, c, 10).  returned that"" %d bytes  were read.\n", fd1, sz); 
            printf("Those bytes are as follows: %s\n", c); 

            while ( read(fd1, c, 20) != 0) {
                printf("%s", c);
            }
       }

    close(fd1);
        
    } else if (argc == 3){
        int fd1 = open(argv[1], O_RDONLY);
        int fd2 = open("foo.txt", O_WRONLY | O_CREAT, 0644);

        if (fd1 < 0){
            printf("Couldn't open file:  %s\n", argv[1]);
            return Error;
        }else{
            int sz; 
            char *c = (char *) calloc(200, sizeof(char)); 
            sz = read(fd1, c, 10); 

            while ( read(fd1, c, 20) != 0) {
                write(fd2, c, 20); 
            }
        }
        close(fd1);
        close(fd2);
    }
}

//REFERENCES:
//https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/




