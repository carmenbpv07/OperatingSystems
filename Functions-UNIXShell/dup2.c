#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int file_desc = open("tricky.txt", O_WRONLY | O_APPEND);
  dup2(file_desc, 1);
  printf("I will be printed in tricky.txt\n");

  return 0;
}