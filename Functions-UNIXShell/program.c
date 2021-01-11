#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("I am program.exe called by execvp()\n");
  printf("program.exe PID = %d\n", getpid());
  return 0;
}