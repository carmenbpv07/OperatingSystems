#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t cpid;
  if (fork() == 0) {
    printf("Child PID = %d\n", getpid());
    exit(0);
  } else {
    cpid = wait(NULL);
    printf("Parent PID = %d\n", getpid());
    printf("Child_wait PID = %d\n", cpid);
  }

  return 0;
}