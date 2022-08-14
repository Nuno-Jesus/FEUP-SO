#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * !Q3: How do you explain the value of variable value in the parent and child processes?
 * When the fork call is executed, the parent process is replicated. The replication includes a full copy of
 * the parent's memory stack. This means a modification in a process doesn't apply in the other. So setting
 * value to 1 in the child, doesn't reflect on the parent. The parent prints 0 and the child prints 1.
 * 
 * The created processes do not use physical addressing memory, only virtual. So both
 * can have the same address for the same variable.
*/

int main(int argc, char **argv){
  pid_t pid;
  int value = 0;

  if ((pid = fork()) == -1){
    perror("fork");
    return EXIT_FAILURE;
  }

  else if (pid == 0){
    /* child process */
    value = 1;
    printf("CHILD: value = %d, addr = %p\n", value, &value);
    return EXIT_SUCCESS;
  }

  else{
    /* parent process */
    if (waitpid(pid, NULL, 0) == -1){
      perror("wait");
      return EXIT_FAILURE;
    }
    printf("PARENT: value = %d, addr = %p\n", value, &value);
    return EXIT_SUCCESS;
  }
}