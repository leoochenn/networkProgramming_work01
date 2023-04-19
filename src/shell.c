#include "../include/myhdr.h"

int main(){
    //  variables 
    char command[MAX_COMMAND_SIZE];
    psCommand_t *parsedCommand = malloc(sizeof(psCommand_t));
    parsedCommand->args = NULL;
    parsedCommand->next = NULL;
    parsedCommand->pipeCount = 0;
    //  set enviroment, and user instructions
    initial();

    while(1){
    printf("%s", "% ");
    //  get user input
    getLine(command);
    //  parse the input command
    parseCommand(command, parsedCommand);
    //  execute the parsed command
    executeCommand(parsedCommand);

    //testing parsedCommand
    // psCommand_t *current = parsedCommand;
    // int i, j;
    // while (current != NULL) {
    //     j = 0;
    //     while (current->args[j] != NULL) {
    //         printf("%s\n", current->args[j]);
    //         j++;
    //     }
    //     printf("pipeCount: %d\n", current->pipeCount);
    //     current = current->next;
    // }


    }
}