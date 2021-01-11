#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 27

/**
    To compile: gcc -o program1.exe program1.c
    To execute: ./program1.exe
**/

int main() {
  char c;
  int shmid;
  key_t key;
  int *shm, *s;
  key = 5678;
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    exit(1);
  }
  if ((shm = shmat(shmid, NULL, 0)) == (int *)-1) {
    perror("shmat");
    exit(1);
  }
  *shm = -1;
  srand(time(NULL));
  while (1) {
    s = shm;
    s++;
    if (*shm == -1) {
      *s = rand() % 100;
      printf("Program1 has generated number: %d\n", *s);
      *shm = -2;
    }
    sleep(4);
  }
  exit(0);
}
