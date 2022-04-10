#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_FLAGS 10
#define MAX_CHARS 4

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

int main(int argc, char **argv){
  char buf[1024];
  char *command;
  pid_t pid;

  char* flags[MAX_CHARS] = {(char*)0};

  /* do this until you get a ^C or a ^D */
  for (;;){
    /* give prompt, read command and null terminate it */
    fprintf(stdout, "$ ");
    if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
      break;

    command[strlen(buf) - 1] = '\0';
    getFlags(command, flags);

    /* call fork and check return value */
    if ((pid = fork()) == -1){
      fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
      continue;
    }

    else if (pid == 0){
      /* child */
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