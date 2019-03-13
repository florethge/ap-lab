#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#define RESET		0
#define BRIGHT		1
#define HIDDEN		8

#define BLACK 		0
#define GREEN		2
#define YELLOW		3
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

time_t currentTime;
struct tm * localT;

void textcolor(int attr, int fg, int bg) {
  char command[13];
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  printf ("%s", command);
}

int typeOfLogger = 0; //STDOUT as default

int initLogger(char *logType){
  if(strcmp ("stdout", logType) == 0 || strcmp ("", logType) == 0){
    typeOfLogger = 0;
    return 1;
  }
  else if(strcmp ("syslog", logType) == 0){
    typeOfLogger = 1;
    return 1;
  }
  return 0;
}

void getTime(){
  char timeHMS[9];
  time(&currentTime);
  localT = localtime(&currentTime);
  strftime(timeHMS, sizeof(timeHMS), "%H:%M:%S", localT);
  fputs(timeHMS,stdout);
}

int infof(const char *format, ...){
  int done;
  va_list args;
  va_start(args, format);
  getTime();
  textcolor (BRIGHT, WHITE, GREEN);
  fputs(" INFO ", stdout);
  textcolor (RESET, WHITE, HIDDEN);
  done = vfprintf(stdout, format, args);
  va_end(args);
  return done;
}
int warnf(const char *format, ...){
  int done;
  va_list args;
  va_start(args, format);
  getTime();
  textcolor (BRIGHT, WHITE, MAGENTA);
  fputs(" WARN ", stdout);
  textcolor (RESET, WHITE, HIDDEN);
  done = vfprintf(stdout, format, args);
  va_end(args);
  return done;
}
int errorf(const char *format, ...){
  int done;
  va_list args;
  va_start(args, format);
  getTime();
  textcolor (BRIGHT, WHITE, CYAN);
  fputs(" ERROR ", stdout);
  textcolor (RESET, WHITE, HIDDEN);
  done = vfprintf(stdout, format, args);
  va_end(args);
  return done;
}
int panicf(const char *format, ...){
  int done;
  va_list args;
  va_start(args, format);
  getTime();
  textcolor (BRIGHT, WHITE, YELLOW);
  fputs(" PANIC ", stdout);
  textcolor (RESET, WHITE, HIDDEN);
  done = vfprintf(stdout, format, args);
  va_end(args);
  return done;
}