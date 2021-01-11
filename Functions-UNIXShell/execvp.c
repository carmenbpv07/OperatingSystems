#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("execvp.exe PID = %d\n", getpid());
  char* args[] = {"./program.exe", NULL};
  execvp(args[0], args);
  printf("Ending, execvp.exe PID = %d\n", getpid());  // This is ignored
  return 0;
}