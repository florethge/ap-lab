#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

#define INFO_LENGTH 50
#define MAX_PROCESSES 2000

//chart implementation found it of stackoverflow
//https://stackoverflow.com/questions/31102232/printing-a-pretty-table-in-c-in-a-linux-terminal
char *header = "|%-6s | %-5s | %-40s | %-10s | %-10s | %-4s | %-10s|\n",
     *sections =	"|-------|--------|------------------------------------------|------------|------------|-----------|-----------|\n",
     *DisplayTable = "| %-5s | %-6s | %-40s | %-10s | %-9.1fM | %-9s | %-10d|\n";

struct mytop_process {
	char name[INFO_LENGTH],
	state[INFO_LENGTH],
	pid[INFO_LENGTH],
	ppid[INFO_LENGTH],
	memory[INFO_LENGTH],
	threads[INFO_LENGTH];
	int openFiles;
};

static const struct mytop_process emptyProcess;
struct mytop_process processes[MAX_PROCESSES];

void clear();
//added two more..
int read_mytop_processes();
int print_mytop_processes();

//Methods implemented

int read_mytop_processes() {
	DIR *d = opendir("/proc/");
	struct dirent *dir;
	FILE *fp;
	char path[30],
		 fdpath[30],
		 info[INFO_LENGTH],
		 c;
	int dataNum,
		procNum = 0,
		opFiles;


	memset(info, 0, INFO_LENGTH);
	strcpy(path, "/proc/");
	strcpy(fdpath, "/proc/");

	while((dir = readdir(d)) != NULL) {
		if(dir->d_name[0] >= 48 && dir->d_name[0] <= 57) {
			dataNum = 0;
			opFiles = 0;

			strcat(path, dir->d_name);
			strcat(path, "/status");

			strcat(fdpath, dir->d_name);
			strcat(fdpath, "/fd");

			fp = fopen(path, "r");

			while(dataNum < 6) {
				switch(dataNum) {
					case 0:
						do {
							c = getc(fp);
						} while(c != 'N' && c != EOF);

						if(c == EOF) {
							fseek(fp, 0L, SEEK_SET);
							strcpy(processes[procNum].name, "");
							break;
						}
						// Looking for "Name"
						if(getc(fp) == 'a' && getc(fp) == 'm' && getc(fp) == 'e' && getc(fp) == ':') {
							do {
								c = getc(fp);
							} while(c == ' ' || c == '\t');

							for(int j = 0; c != '\n'; j++) {
								info[j] = c;
								c = getc(fp);
							}
							strcpy(processes[procNum].name, info);
							fseek(fp, 0L, SEEK_SET);
						}
						else {
							dataNum = -1;
						}
						break;
						case 1:
							do {
								c = getc(fp);
							} while(c != 'S' && c != EOF);

							if(c == EOF) {
								fseek(fp, 0L, SEEK_SET);
								break;
							}
							// Looking for "State"
							if(getc(fp) == 't' && getc(fp) == 'a' && getc(fp) == 't' && getc(fp) == 'e' && getc(fp) == ':') {
								do {
									c = getc(fp);
								} while(c != '(');

								c = getc(fp);

								for(int j = 0; c != ')'; j++) {
									info[j] = c;
									c = getc(fp);
								}
								strcpy(processes[procNum].state, info);
								fseek(fp, 0L, SEEK_SET);
							}
							else {
								dataNum = 0;
							}
							break;
							case 2:
								do {
									c = getc(fp);
								} while(c != 'P' && c != EOF);

								if(c == EOF) {
									fseek(fp, 0L, SEEK_SET);
									break;
								}
								// Looking for "Pid"
								if(getc(fp) == 'i' && getc(fp) == 'd' && getc(fp) == ':') {
									do {
										c = getc(fp);
									} while(c == ' ' || c == '\t');

									for(int j = 0; c != '\n'; j++) {
										info[j] = c;
										c = getc(fp);
									}
									strcpy(processes[procNum].pid, info);
									fseek(fp, 0L, SEEK_SET);

								}
								else {
									dataNum = 1;
								}
								break;
							case 3:
								do {
									c = getc(fp);
								} while(c != 'P' && c != EOF);

								if(c == EOF) {
									fseek(fp, 0L, SEEK_SET);
									break;
								}
								// Looking for "PPid"
								if(getc(fp) == 'P' && getc(fp) == 'i' && getc(fp) == 'd' && getc(fp) == ':') {
									do {
										c = getc(fp);
									} while(c == ' ' || c == '\t');

									for(int j = 0; c != '\n'; j++) {
										info[j] = c;
										c = getc(fp);
									}
									strcpy(processes[procNum].ppid, info);
									fseek(fp, 0L, SEEK_SET);
								}
								else {
									dataNum = 2;
								}
								break;
								case 4:
									do {
										c = getc(fp);
									} while(c != 'V' && c != EOF);
									if(c == EOF) {
										fseek(fp, 0L, SEEK_SET);
										break;
									}
									// Looking for "VmRSS"
									if(getc(fp) == 'm' && getc(fp) == 'R' && getc(fp) == 'S' && getc(fp) == 'S' && getc(fp) == ':') {
										do {
											c = getc(fp);
										} while(c == ' ' || c == '\t');

										for(int j = 0; c != ' '; j++) {
											info[j] = c;
											c = getc(fp);
										}
										strcpy(processes[procNum].memory, info);

										fseek(fp, 0L, SEEK_SET);
									}
									else {
										dataNum = 3;
									}
									break;
									case 5:
										do {
											c = getc(fp);
										} while(c != 'T' && c != EOF);

										if(c == EOF) {
											fseek(fp, 0L, SEEK_SET);
											break;
										}
										// Looking for "Threads"
										if(getc(fp) == 'h' && getc(fp) == 'r' && getc(fp) == 'e' && getc(fp) == 'a' && getc(fp) == 'd' && getc(fp) == 's' && getc(fp) == ':') {

											do {
												c = getc(fp);
											} while(c == ' ' || c == '\t');

											if(c == '\n') {
												break;
											}

											for(int j = 0; c != '\n'; j++) {
												info[j] = c;
												c = getc(fp);
											}
											strcpy(processes[procNum].threads, info);
										}
										else {
											dataNum = 4;
										}
										break;
				}
				memset(info, 0, INFO_LENGTH);
				dataNum++;
				c = '\0';
			}

			fclose(fp);
			DIR *fdd = opendir(fdpath);
			struct dirent *fd_dir;
			while((fd_dir = readdir(fdd)) != NULL) {
				opFiles++;
			}
			closedir(fdd);

			processes[procNum].openFiles = opFiles - 2;

			strcpy(fdpath, "/proc/");
			strcpy(path, "/proc/");
			procNum++;
		}
	}
	closedir(d);
	return 0;
}

static void saveProcesses(int signo) {
	FILE *fp;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char fileName[30];
	float memory_;

	sprintf(fileName, "mytop_status_%d-%d-%d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	fp = fopen(fileName, "w");
	fprintf(fp, header, " PID", "Parent", "Name", "State", "Memory", "# Threads", "Open Files");
	fprintf(fp, sections);

	for(int i = 0; processes[i].name[0] != '\0'; i++) {
		memory_ = atof(processes[i].memory) / 1000;
		fprintf(fp, DisplayTable, processes[i].pid, processes[i].ppid, processes[i].name, processes[i].state, memory_, processes[i].threads, processes[i].openFiles);
	}
	printf("\n Dashboard saved to %s\n", fileName);
	fclose(fp);
	sleep(4);
}

int print_mytop_processes() {
	int i = 0;
	float memory_;

	printf(header, "PID", "Parent", "Name", "State", "Memory", "# Threads", "Open Files");
	printf(sections);

	while(processes[i].name[0] != '\0') {
		memory_ = atof(processes[i].memory) / 1000;
		printf(DisplayTable, processes[i].pid, processes[i].ppid, processes[i].name, processes[i].state, memory_, processes[i].threads, processes[i].openFiles);
		i++;
	}
	return 0;
}

void clear() {
	for(int i = 0; processes[i].name[0] != '\0'; i++) {
		processes[i] = emptyProcess;
	}
	printf("\e[1;1H\e[2J");
}

int main(){
	// Place your magic here
	if(signal(SIGINT, saveProcesses) == SIG_ERR) {
		printf("Unable to get signal\n");
	}
	while(1) {
		read_mytop_processes();
		print_mytop_processes();
		sleep(4);
		clear();
	}
	return 0;
}

