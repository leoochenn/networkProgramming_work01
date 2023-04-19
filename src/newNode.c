#include "../include/myhdr.h"

void newNode(psCommand_t* current){
    psCommand_t *next = malloc(sizeof(psCommand_t));
    next->next = NULL;
    next->args = NULL;
    next->pipeCount = current->pipeCount;
    current->next = next;
}

