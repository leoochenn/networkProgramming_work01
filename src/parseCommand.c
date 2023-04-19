#include "../include/myhdr.h"

void parseCommand(char *command, psCommand_t *parsedCommand) {
    char *ptr = strtok(command, "|");
    char **split = malloc(50 * sizeof(char *));
    int splitCount = 0;

    while(ptr != NULL) {
        split[splitCount++] = ptr;
        ptr = strtok(NULL, "|");
    }

    psCommand_t *current = parsedCommand;
    current->pipeCount = splitCount;

    int i, j;
    for (i = 0; i < splitCount; i++) {
        current->args = malloc(256 * sizeof(char *));
        char *token = strtok(split[i], " \n");
        j = 0;
        while (token != NULL) {
            current->args[j] = malloc(strlen(token) + 1);
            strcpy(current->args[j], token);
            j++;
            token = strtok(NULL, " \n");
        }
        current->args[j] = NULL;
        if (i != splitCount - 1) {
            newNode(current);
            current = current->next;
        }
    }
}
