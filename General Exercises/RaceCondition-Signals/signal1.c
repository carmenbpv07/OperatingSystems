#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int signum) {
  printf("Caught signal %d, coming out...\n", signum);
}
int main() {
  signal(SIGINT, sighandler);

  while (1) {
    printf("Going to sleep for a second...\n");
    sleep(1);
  }
  return (0);
}
