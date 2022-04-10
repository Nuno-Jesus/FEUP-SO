#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_FLAGS 101
#define SIZE 100
#define MAX_CHARS 200

void getFlags(char* input, char** flags){
  flags[0] = strtok(input, " ");
  for(int i = 1; i < MAX_FLAGS; i++){
    flags[i] = strtok(NULL, " ");
    if(flags[i] == NULL){
      flags[i] = (char*)0;
      break;
    }
  }
}

void myhistory(int size, char** commands){
  for(int i = 0; i < size; i++)
    puts(commands[i]);
}

int main(int argc, char **argv){
  if(argc > 1){
    myhistory(argc - 1, argv);
    return EXIT_SUCCESS;
  }

  char buf[1024];
  char* command, *flags[MAX_FLAGS] = {(char*)0}, history[SIZE][MAX_CHARS] = {};
  int size = 0;
  pid_t pid;


  /* do this until you get a ^C or a ^D */
  for (;;){
    /* give prompt, read command and null terminate it */
    fprintf(stdout, "$ ");
    if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
      break;

    command[strlen(buf) - 1] = '\0';
    strcpy(history[size++], command);
    getFlags(command, flags);
    
    //If the inputed commmand was myhistory
    if(!strcmp("myhistory", command)){
      command = argv[0];
      flags[0] = command;
      for(int i = 0; i < size; i++){
        flags[i + 1] = history[i];
      }
    }

    /* call fork and check return value */
    if ((pid = fork()) == -1){
      fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
      continue;
    }
    
    /* child */
    else if (pid == 0){
      execvp(command, flags);
      /* if I get here "execlp" failed */
      fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf, strerror(errno));
      /* terminate with error to be caught by parent */
      exit(EXIT_FAILURE);
    }

    /* shell waits for command to finish before giving prompt again */
    if ((pid = waitpid(pid, NULL, 0)) < 0)
      fprintf(stderr, "%s: waitpid error: %s\n", argv[0], strerror(errno));
  }

  exit(EXIT_SUCCESS);
}