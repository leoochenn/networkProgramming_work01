#include "../include/myhdr.h"

void executeCommand(psCommand_t *command)
{
    char _quit[] = "quit";
    char _cd[] = "cd";
    char _printenv[] = "printenv";
    char *firstCommand = command->args[0];

    if (strcmp(firstCommand, _quit) == 0)
    {
        printf("----------exit shell----------\n");
        exit(EXIT_SUCCESS);
    }
    // else if(strcmp(firstCommand, _cd) == 0){
    //     printf("i was in here\n");
    //     chdir(command->args[1]);
    //     char s[100];
    //     printf("cwd%s\n", getcwd(s, 100));
    //     return;
    // }
    else if (strcmp(firstCommand, _printenv) == 0)
    {
        printf("%s\n", getenv(command->args[1]));
        return;
    }
    int numberOfChild = command->pipeCount;

    if (numberOfChild == 1)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (execvp(command->args[0], command->args) < 0)
            {
                perror("execvp failed no such a command");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(NULL);
            return;
        }
    }

    // printf("number of child: %d", numberOfChild);
    int pipeLink[numberOfChild - 1][2];

    for (int i = 0; i < numberOfChild; i++)
    {
        if (pipe(pipeLink[i]) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    char **cmd[numberOfChild];
    for(int i = 0; i < numberOfChild; i++){
        cmd[i] = command->args;
        command = command->next;
        //printf("%s\n", *cmd[i]);

    }

    
    int numberOfProcess = 0;

    for (int i = 0; i < numberOfChild; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            // This is a child process
            if (i == 0)
            {
                // First child process
                close(pipeLink[0][0]);               // Close the read end of the first pipe
                dup2(pipeLink[0][1], STDOUT_FILENO); // Redirect standard output to the write end of the first pipe
                close(pipeLink[0][1]);               // Close the write end of the first pipe
            }
            else if (i == numberOfChild - 1)
            {
                // Last child process

                close(pipeLink[i - 1][1]);              // Close the write end of the previous pipe
                dup2(pipeLink[i - 1][0], STDIN_FILENO); // Redirect standard input to the read end of the previous pipe
                close(pipeLink[i - 1][0]);              // Close the read end of the previous pipe
            }
            else
            {
                // Middle child process
 
                close(pipeLink[i - 1][1]);              // Close the write end of the previous pipe
                dup2(pipeLink[i - 1][0], STDIN_FILENO); // Redirect standard input to the read end of the previous pipe
                close(pipeLink[i - 1][0]);              // Close the read end of the previous pipe
                close(pipeLink[i][0]);                  // Close the read end of the current pipe
                dup2(pipeLink[i][1], STDOUT_FILENO);    // Redirect standard output to the write end of the current pipe
                close(pipeLink[i][1]);                  // Close the write end of the current pipe
            }

			for(int j = 0; j < numberOfChild; j++){
					close(pipeLink[j][0]);
					close(pipeLink[j][1]);
			}

            // Execute the child process command
           
            if (execvp(*cmd[i], cmd[i]) < 0)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else{
            numberOfProcess++;
            //printf("number of process: %d\n", numberOfProcess);
        }
    }

    // Close all pipe ends in the parent process
    for (int i = 0; i < numberOfChild - 1; i++)
    {
        close(pipeLink[i][0]);
        close(pipeLink[i][1]);
    }

    // Wait for all child processes to exit
    pid_t pid;
    while (numberOfProcess > 0)
    {
        pid = wait(NULL);
        if(pid == -1){
            if(errno == ECHILD){
                exit(EXIT_SUCCESS);
            }
            else{
                perror("wait error");
                exit(EXIT_FAILURE);
            }

        }
        //printf("number of process re: %d\n", numberOfProcess);
        numberOfProcess--;
    }
}
