#include <stdio.h>
/* Write a program to remove all comments from a C program,
   Don't forget to handle quoted strings and character constants
   properly. C Comments do not nest */
main(){
int first,second ,eatChar,lookAhead,previous;
	first = getchar();
while((second = getchar()) != EOF){
if(first == '/')
if(second == '/'){
//Delete til the end of the line
while((eatChar=getchar())!=EOF && eatChar != '\n')
					;
//Print the newline
putchar(eatChar);
			}else if(second == '*'){
//Bit harder, read until the next */
while((eatChar = getchar()) != EOF){
if(eatChar == '*'){
						lookAhead = getchar();
if(lookAhead == '/')
goto next;
else if(lookAhead == '*')
ungetc(first,stdin);
					}
				}
			}
		next:
if(first == '/' && second =='/')
			;
else if(first == '/' && second == '*')
			;
else if(previous == '/' && first == '/')
			;
else if(previous == '/' && first == '*')
			;
else
putchar(first);
		previous=first;
		first=second;
	}
putchar(first);
printf("\n");
}