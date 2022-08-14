#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFERSIZE 4096

void print_usage(char* command){
    printf("Usage: %s filename", command);
    exit(EXIT_FAILURE);
}

void read_file(){

}

int main(int argc, char *argv[]){
    if(argc != 2)
        print_usage(argv[0]);

    int nbytes, fd[2];
    pid_t pid;
    char line[BUFFERSIZE];
    ssize_t size;

    if (pipe(fd) < 0){
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
        perror("fork error");
        exit(EXIT_FAILURE);
    }

/* parent */
    else if (pid > 0){
        close(fd[READ_END]);
        printf("Parent process with pid %d\n", getpid());
        printf("Messaging the child process (pid %d):\n", pid);
        
        int file = open(argv[1], O_RDONLY);
        if(file == -1){
            printf("\n\t----- ERROR: UNABLE TO LOCATE %s -----\n\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        while(1){
            size = read(file, line, BUFFERSIZE);

            if((nbytes = write(fd[WRITE_END], line, strlen(line))) < 0){
                fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
            }

            close(fd[WRITE_END]);
            /* wait for child and exit */
            if (waitpid(pid, NULL, 0) < 0){
                fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
            }

            if(size != BUFFERSIZE) break;
        }
        
        close(file);
        exit(EXIT_SUCCESS);
    }

    else
    {
        /* child */
        close(fd[WRITE_END]);
        printf("Child process with pid %d\n", getpid());
        printf("Receiving message from parent (pid %d):\n", getppid());

        if ((nbytes = read(fd[READ_END], line, BUFFERSIZE)) < 0){
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }

        close(fd[READ_END]);
        /* write message from parent */
        write(STDOUT_FILENO, line, nbytes);
        /* exit gracefully */
        exit(EXIT_SUCCESS);
    }
}