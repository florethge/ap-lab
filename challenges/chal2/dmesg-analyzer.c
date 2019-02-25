#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define Error 1
#define RPT_FILE "report.txt"

void analizeLog(char *logFile, char *report);

struct logFile{
    char *type;
    char *info[100];
    int id;
};

struct logFile logs[1000];
int pointer = 0;

void Concat2Str(char *type, char *info){

    for(int i = 0; i < pointer; i++) {
        if(*logs[i].type == *type) {
            logs[i].info[logs[i].id] = (char *)malloc(sizeof(char)*1000);
            strcpy(logs[i].info[logs[i].id], info);
            logs[i].id++;
            return;
            }
    }
    logs[pointer].type = (char *)malloc(sizeof(char)*1000);
    logs[pointer].info[0] = (char *)malloc(sizeof(char)*1000);
    strcpy(logs[pointer].type, type);
    strcpy(logs[pointer].info[0], info);
    logs[pointer].id = 1;
    pointer++;

}

void Look4Lines(char *line){

	bool flag = true;
    bool type_flag = false;
    bool verified = false;
    
    char *t = (char *)malloc(sizeof(char) * 1); 
    char *aux = (char *)malloc(sizeof(char) * 1);
    char *type = (char *)malloc(sizeof(char) * 1000);
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    char *info = (char *)malloc(sizeof(char) * 1000);

    
    for(int i = 0; i < 15; i++) {
        (*t = *line);
        strcat(info, t);
        line++;
    }    

    while((*t = *line) != '\0') {
        *aux = *++line; 
        --line;
        if(*t == ':' && *aux == ' ' && !verified) {
            ++line;
            *t = *line;
            strcpy(type, buffer);
            flag = false;
            type_flag = true;
            verified = true;
        }
        if(flag) {
            strcat(buffer, t);
        }else {
            strcat(info, t);
        }
        ++line;  
    }
    if(!type_flag) {
        strcat(type, "General");
        strcat(info, buffer);
    }
    Concat2Str(type, info);
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here----.
    FILE *FInput, *FOutput;
    int c;
    char *f = (char *)malloc(sizeof(char)*1);

    if((FInput = open(logFile, O_RDONLY)) < 0){
	printf("Cannot open your file");
    }
    
    FOutput = fopen(report, "w");

    char *line = (char *)malloc(sizeof(char)*1000);

    while((c = read(FInput, f, 1)) > 0) {
	if( *f == '\n') {
	    strcat(line, "\n\0");
	    Look4Lines(line);
	    *line = NULL;
	    
	} else {
	    strcat(line, f);
        }
    }

    for(int k = 0; k < pointer; k++) {
        fprintf(FOutput, logs[k].type);
	    fprintf(FOutput, "\n");
	    write(1, logs[k].type, 100);
	    write(1, "\n", 1);
	
    for(int j = 0; j < logs[k].id; j++) {
	    fprintf(FOutput, "\t");
	    fprintf(FOutput, logs[k].info[j]);
	    write(1, "\t", 1);
	    write(1, logs[k].info[j], 500);
        }
    }
    close(FInput);
    fclose(FOutput);
    printf("Report was successfully generated, find it here: [%s]\n", report);
}

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Warning! Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }
    analizeLog(argv[1], RPT_FILE);
    return 0;
}
