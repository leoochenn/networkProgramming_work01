#ifndef MYHDR_H
#define MYHDR_H

//include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


//define
#define MAX_COMMAND_SIZE 5000
#define READ_END 0
#define WRITE_END 1

//struct
typedef struct cmd{
    struct cmd *next;
    char **args;
    int pipeCount;
}psCommand_t;

//functions
void initial();
void getLine(char *);
void parseCommand(char *, psCommand_t *);
void newNode(psCommand_t*);
void executeCommand(psCommand_t*);
// void doChild(int[][2], psCommand_t *, int);
// void doParent(int*, psCommand_t*, int);
void doChile(int, psCommand_t*);

#endif