#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
    To compile: gcc -o program3.exe program3.c -lpthread
    To execute: ./program3.exe
**/

#define SEM_PATH "/S1"

#define SHMSZ 27

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
  sem_t *sem_id = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1);
  while (1) {
    sem_wait(sem_id);
    s = shm;
    s++;
    if (*shm == -3 && (*s) % 2 != 0) {
      printf("Program3 found an odd number: %d\n", *s);
    }
    *shm = -1;
    sem_post(sem_id);
  }
  exit(0);
}