#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  printf("I am program2.exe called by execvp()\n");
  printf("program2.exe PID = %d\n", getpid());
  printf("program2.exe parametro 0 = %s\n", argv[0]);
  printf("program2.exe parametro 1 = %s\n", argv[1]);
  return 0;
}