#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("execvp2.exe PID = %d\n", getpid());
  char* args[] = {"./program2.exe", "p1", "p2", "p3", NULL};
  execvp(args[0], args);
  printf("Ending, execvp2.exe PID = %d\n", getpid());  // This is ignored
  return 0;
}