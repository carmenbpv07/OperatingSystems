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

#include <iostream>
#include <queue>
#include <thread>

/**
    To compile: g++ -std=c++11 main.cpp -o main -lpthread
    To execute: ./main
**/
#define SEM_PATH1 "/S1"
#define SEM_PATH2 "/S2"

#define SHMSZ 27

using namespace std;

const int n_numbers = 10;  // The amount of numbers

queue<int> general_queue;

// This thread generates random numbers and adds them to the queue
void generator() {
  srand(time(NULL));
  for (int i = 1; i <= n_numbers; i++) {
    general_queue.push(rand() % 100);
  }
}

int main() {
  thread first(generator);

  int shmid;
  int *shm, *s;
  key_t key = 5678;

  // shmget -> Returns the ID of the shared memory associated with the key
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    exit(1);
  }
  // shmat -> Returns the memory address of the shared segment
  if ((shm = (int *)shmat(shmid, NULL, 0)) == (int *)-1) {
    perror("shmat");
    exit(1);
  }

  sem_t *sem_id1 =
      sem_open(SEM_PATH1, O_CREAT, S_IRUSR | S_IWUSR, 0);  // For even numbers
  sem_t *sem_id2 =
      sem_open(SEM_PATH2, O_CREAT, S_IRUSR | S_IWUSR, 0);  // For odd numbers

  while (1) {
    s = shm;
    if (!general_queue.empty()) {
      *s = general_queue.front();  // Extracting the number from the queue and
                                   // writing it to shared memory
      general_queue.pop();
      printf("Program1 has generated number: %d\n", *s);
      // sem_post -> To release or signal a semaphore, increases (unlocks) the
      // semaphore pointed by sem_id
      if ((*s) % 2 == 0) {
        sem_post(sem_id1);  // For even numbers
      } else {
        sem_post(sem_id2);  // For odd numbers
      }
    }
    sleep(4);
  }

  first.join();

  return 0;
}