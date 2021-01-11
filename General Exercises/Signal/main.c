#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** When this program receives a signal, it will execute programThread.exe
    To compile: gcc -o main.exe main.c
    To execute: ./main.exe
**/

void sighandler(int signum) {
  printf("Caught signal %d.\n", signum);
  char* args[] = {"./programThreads.exe", NULL};
  execvp(args[0], args);
}

int main() {
  int counter = 0;
  signal(SIGINT, sighandler);

  while (1) {
    printf("This is an infinite loop...%i\n", ++counter);
    sleep(1);
  }
  return (0);
}