#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t cpid;
  int state;
  if (fork() == 0) {
    printf("Child PID = %d\n", getpid());
    exit(0);
  } else {
    cpid = wait(&state);
    printf("Parent PID = %d\n", getpid());
    printf("Child_wait PID = %d\n", cpid);
  }
  if (WIFEXITED(state)) {
    printf("Exit status: %d\n", WEXITSTATUS(state));
  } else if (WIFSIGNALED(state)) {
    psignal(WTERMSIG(state), "Exit signal\n");
  }

  return 0;
}