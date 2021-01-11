#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void forkexample() {
  if (fork() == 0) {
    printf("Child!\n");
  } else {
    printf("Parent!\n");
  }
}

int main() {
  forkexample();
  return 0;
}