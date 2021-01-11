#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("PI2 = %d\n", getpid());
  char *args[] = {"./program1.exe", NULL};
  int stat;
  if (fork() == 0) {  // child
    execvp(args[0], args);
  } else {
    wait(&stat);
  }
  if (WIFEXITED(stat)) {
    printf("Exit status: %d\n", WEXITSTATUS(stat));
  } else if (WIFSIGNALED(stat)) {
    psignal(WTERMSIG(stat), "Exit signal");
  }
  return 0;
}
