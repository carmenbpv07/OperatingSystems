#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHMSZ 27

/**
    To compile: gcc -o program2.exe program2.c
    To execute: ./program2.exe
**/

int main() {
  int shmid;
  key_t key;
  int *shm, *s;
  key = 5678;
  if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
    perror("shmget");
    exit(1);
  }
  if ((shm = shmat(shmid, NULL, 0)) == (int *)-1) {
    perror("shmat");
    exit(1);
  }
  while (1) {
    s = shm;
    s++;
    if (*shm == -2 && (*s) % 2 == 0) {
      printf("Program2 found an even number: %d\n", *s);
      *shm = -1;
    } else if (*shm == -2) {
      *shm = -3;
    }
    sleep(4);
  }
  exit(0);
}