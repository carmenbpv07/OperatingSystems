#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("PI1 = %d\n", getpid());
  printf("I am program1.c called by execvp() and I have a division by zero\n");
  int x = 10, w = 2, i;
  for (i = 0; i < 4; i++) {
    int y = x / w;
    w--;
  }
  return 0;
}
