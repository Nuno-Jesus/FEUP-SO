#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define FLAGS 10

char cmd1[FLAGS + 2][5] = {(char*)0};
char cmd2[FLAGS + 2][5] = {(char*)0};


void retrieve_flags(char* input, int command){
    if(command == 1){
        strcpy(strtok(input, " "), cmd1[0]);
        for (int i = 1; i < FLAGS; i++){
            strcpy(strtok(input, " "), cmd1[i]);
            if (cmd1[i] == NULL)
            {
                strcpy(cmd1[i], (char*)0);
                break;
            }
        }   
    }

    else if (command == 2){
        strcpy(strtok(input, " "), cmd2[0]);
        for (int i = 1; i < FLAGS; i++){
            strcpy(strtok(input, " "), cmd2[i]);
            if (cmd2[i] == NULL)
            {
                strcpy(cmd2[i], (char*)0);
                break;
            }
        }
    }
    
}

void print_usage(char* command){
    printf("%s tube \"Command1 (| Command2)+\"\n", command);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    if(argc != 3)
        print_usage(argv[0]);

    int i = 0;
    //Gets the first command with the flags
    retrieve_flags(strtok(argv[2], "|"));
    retrieve_flags(strtok(NULL, "|"));
    
    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0){
        perror("pipe(): ");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
       perror("fork(): ");
       exit(EXIT_FAILURE);
    }

    if (pid > 0){
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd[WRITE_END]);
        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0){
            perror("execvp(): ");
            exit(EXIT_FAILURE);
        }
    }

    else{
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd[READ_END]);
        if (execvp(cmd2[0], cmd2) < 0){
            perror("execvp(): ");
            exit(EXIT_FAILURE);
        }
    }
}