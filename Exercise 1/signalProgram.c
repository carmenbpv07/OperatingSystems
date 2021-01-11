#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/** This program will send a signal to the process with process ID: PID entered by user.
    To compile: gcc -o signalProgram.exe signalProgram.c
    To execute: ./signalProgram.exe
**/

int main() {
  int PID;
  printf("Enter Process ID: ");
  scanf("%d", &PID);
  kill(PID, SIGINT);
  return 0;
}