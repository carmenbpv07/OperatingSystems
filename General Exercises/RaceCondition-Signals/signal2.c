#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int signum) {
  printf("Caught signal %d, coming out...\n", signum);
}
int main() {
  int c = 0;
  signal(SIGINT, sighandler);

  while (1) {
    printf("Going to sleep for a second...%i\n", ++c);
    sleep(1);
  }
  return (0);
}
