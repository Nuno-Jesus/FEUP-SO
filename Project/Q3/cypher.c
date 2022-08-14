#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "StringPair.h"
#include "StringPairList.h"
#include "utils.h"

#define MAX_TEXT_SIZE 4096
#define MAX_WORD_SIZE 25

#define READ_END 0
#define WRITE_END 1

StringPairList* list;
char text[MAX_TEXT_SIZE] = {'\0'};

/**
 * @brief Checks if any of the words in buffer are in the string pairs previously read
 * @param buf Buffer to be checked
 * @param newBuf Buffer that will contain the altered words
 */
void replace_words(char *buf, char *newBuf){
    char *token = NULL;
    char newWord[MAX_WORD_SIZE] = {'0'};
    token = strtok(buf, " ");

    while (token != NULL){
        if (is_in_list(list, token, newWord))
            strcat(newBuf, newWord);
        else
            strcat(newBuf, token);
        strcat(newBuf, " ");
        memset(newWord, 0, strlen(newWord));
        token = strtok(NULL, " ");
    }
}

int main(int argc, char **argv){
    if (argc > 1){
        printf("Program does not accept arguments.\n");
        exit(EXIT_FAILURE);
    }
    
    int fd1[2], fd2[2];
    char chunk[CHUNK_SIZE] = {'\0'};
    int bytes;
    pid_t pid;

    /* Reads the strings into an appropriated data structure */
    list = get_pairs();

    /* Reads the text to be modified */
    get_text(text);

    /* Opening the first pipe */
    if (pipe(fd1) < 0){
        perror("pipe():");
        exit(EXIT_FAILURE);
    }

    /* Opening the second pipe */
    if (pipe(fd2) < 0){
        perror("pipe():");
        exit(EXIT_FAILURE);
    }

    /* Forking parent process */
    if ((pid = fork()) < 0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    // Child
    else if (pid == 0){
        close(fd1[WRITE_END]);

        char buf[MAX_TEXT_SIZE] = {'\0'};

        /* Read data from the pipe */
        while (1)
        {
            bytes = read(fd1[READ_END], chunk, CHUNK_SIZE - 1);
            chunk[bytes] = '\0';
            strcat(buf, chunk);

            if (bytes < CHUNK_SIZE - 1)
                break;
        }

        close(fd1[READ_END]);

        close(fd2[READ_END]);

        /* Changes the words on the text read */
        char new_buf[MAX_TEXT_SIZE] = {'\0'};
        replace_words(buf, new_buf);

        /* Send data to the pipe */
        if (write(fd2[WRITE_END], new_buf, strlen(new_buf)) == -1)
        {
            perror("write()");
            exit(EXIT_FAILURE);
        }
        close(fd2[WRITE_END]);
        
        free_list(list);

        exit(EXIT_SUCCESS);
    }

    // Parent
    else
    {
        close(fd1[READ_END]);

        /* Write data to the pipe */
        if (write(fd1[WRITE_END], text, strlen(text)) == -1)
        {
            perror("write()");
            exit(EXIT_FAILURE);
        }

        close(fd1[WRITE_END]);

        wait(NULL);

        close(fd2[WRITE_END]);

        char alteredText[MAX_TEXT_SIZE] = {'\0'};

        /* Read data from the pipe */
        while (1){
            bytes = read(fd2[READ_END], chunk, CHUNK_SIZE - 1);
            chunk[bytes] = '\0';
            strcat(alteredText, chunk);
            if (bytes < CHUNK_SIZE - 1)
                break;
        }

        /* Write data to the standard output*/
        write(STDOUT_FILENO, alteredText, strlen(alteredText));

        close(fd2[READ_END]);

        free_list(list);

    }
    return 0;
}