#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
    To compile: gcc -o program1.exe program1.c -lpthread
    To execute: ./program1.exe
**/

#define SEM_PATH "/S1"
#define SHMSZ 27

int main(int argc, char *argv[]) {
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
  sem_t *sem_id = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1);
  *shm = -1;
  srand(time(NULL));
  while (1) {
    sem_wait(sem_id);
    s = shm;
    s++;
    if (*shm == -1) {
      *s = rand() % 100;
      printf("Program1 has generated number: %d\n", *s);
      *shm = -2;
    }
    sem_post(sem_id);
    sleep(4);
  }

  return 0;
}
