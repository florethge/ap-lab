//str-main.c
#include <stdio.h>

int strrlen(char *str);
char stradd(char *origin, char *addition);
int strfind(char *substr, char *str3);

int main( int argc, char *argv[]) {

    printf("Initial Lenght : %d\n", strrlen("originalVeryLongString"));
	printf("New String: %s\n", stradd("originalVeryLongString", "Addition"));
    printf("Initial Lenght : %d\n", strfind("Add", stradd("originalVeryLongString", "Addition")));
    
}


