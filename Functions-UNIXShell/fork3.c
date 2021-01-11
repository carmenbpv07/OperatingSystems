#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void forkexample() {
  if (fork() == 0) {
    printf("Child PID= %d\n", getpid());
  } else {
    printf("Parent PID= %d\n", getpid());
  }
}

int main() {
  forkexample();
  return 0;
}