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
    To compile: g++ -std=c++11 odd.cpp -o odd -lpthread
    To execute: ./odd
**/

#define SEM_PATH2 "/S2"
#define SEM_PATH3 "/S3"

#define SHMSZ 27

int main() {
  int shmid;
  int *shm, *s;
  key_t key = 5678;

  if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
    perror("shmget");
    exit(1);
  }
  if ((shm = (int *)shmat(shmid, NULL, 0)) == (int *)-1) {
    perror("shmat");
    exit(1);
  }

  sem_t *sem_id2 = sem_open(SEM_PATH2, O_CREAT, S_IRUSR | S_IWUSR, 0);
  sem_t *sem_id3 = sem_open(SEM_PATH3, O_CREAT, S_IRUSR | S_IWUSR, 1);
  while (1) {
    sem_wait(sem_id2);
    s = shm;
    printf("Program3 found an odd number: %d\n", *s);
    sem_post(sem_id3);
  }

  exit(0);
}