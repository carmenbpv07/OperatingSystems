#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

/** This program will be called by main.exe when receives a signal from
    signalProgram.exe 
    To compile: g++ -std=c++0x -pthread -o programThreads.exe programThreads.cpp
**/

void printNumbersOdd() {
  int file2 = open("fileI.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
  dup2(file2, 1);
  close(file2);
  for (int i = 1; i <= 10000; i++) {
    if (i % 2 == 1) {
      printf("%d\n", i);
    }
  }
}

void printNumbersEven() {
  int file1 = open("fileP.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
  dup2(file1, 1);
  close(file1);
  for (int i = 1; i <= 10000; i++) {
    if (i % 2 == 0) {
      printf("%d\n", i);
    }
  }
}

int main() {
  std::cout << "This is the program with 2 threads...\n";
  std::thread thread1(printNumbersEven);
  thread1.join();
  std::thread thread2(printNumbersOdd);
  thread2.join();

  return 0;
}