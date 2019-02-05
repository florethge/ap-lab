//strlib.c
#include <stdio.h>
#include <string.h>
char str[80];
int strrlen(char *str){
    int len = strlen(str);
    printf("Initial Lenght : %d\n", len);
    return len;
}
char * stradd(char *origin, char *addition){
    char * str3 = (char *) malloc(1 + strlen(origin)+ strlen(addition));
    strcpy(str3, origin);
    strcat(str3, addition);
    printf("New String: %s\n", str3);
    return str3;
}
int strfind(char *substr, char *str3){
    if(strstr( str3, substr) != NULL) {
        printf("True");
        retunr 1;
    }
    else{
        printf("False");
        return 0;
    }
    
}
/*
int main() {
    strrlen("originalVeryLongString");
    stradd("originalVeryLongString", "Addition");
    strfind("Add", stradd("originalVeryLongString", "Addition"));
    
}
*/