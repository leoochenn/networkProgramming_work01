#include "../include/myhdr.h"

void initial(){
	//set the enviroment to our own bin directory.
	if(setenv("PATH", "bin:./bin", 1)){
		perror("initial setenv failed");
	}

	printf("Wellcome to my shell\n");
	printf("type ""quit"" to exit the shell\n");
}