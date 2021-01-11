#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 80  // The maximum length command

/** Chapter 3: Processes
    Programming Projects P-12
    Compile : gcc -o shell.exe shell.c
    Execute : ./shell.exe
    To stop a process enter stop and the PID: stop 628
    To continue a process enter continue and the PID: continue 628
**/

char commands[100][MAXLINE];  // Command history
int limit = 0;

void readCommand(char *currentCommand[], int *amp, int *tam, int *sig) {
  char command[MAXLINE];

  int size = read(STDIN_FILENO, command, MAXLINE);

  // Replacing '\n' with the Null character
  command[size - 1] = '\0';

  // For managing the History Feature
  if (strcmp(command, "!!") == 0) {
    if (limit == 0) {
      *tam = 0;
      printf("No commands in history.\n");
    } else {
      int z, k;
      for (z = 0; z < limit; z++) {
        printf("  %d  ", z + 1);
        for (k = 0; commands[z][k] != '\0'; k++) {
          printf("%c", commands[z][k]);
        }
        printf("\n");
      }
    }
    return;
  }

  // For saving the current command in the history
  int i;
  for (i = 0; i < size; i++) {
    commands[limit][i] = command[i];
  }
  limit++;

  // For checking if the command ends with an &
  if (command[size - 2] == '&') {
    *amp = 1;
    command[size - 2] = '\0';
  }

  *tam = 0;
  char *tmp = strtok(command, " ");
  while (tmp != NULL) {
    *tam += 1;
    currentCommand[*tam - 1] = strdup(tmp);
    tmp = strtok(NULL, " ");
  }
  currentCommand[*tam] = NULL;

  if (strcmp(currentCommand[0], "stop") == 0 ||
      strcmp(currentCommand[0], "continue") == 0) {
    *sig = 1;
  }
}

int main(void) {
  char *currentCommand[MAXLINE / 2 + 1];
  int shouldRun = 1;
  while (shouldRun) {
    printf("osh> ");
    fflush(stdout);
    int amp = 0, tam = 0, sig = 0, PID;
    readCommand(currentCommand, &amp, &tam, &sig);
    if ((PID = fork()) == 0) {  // Child process
      // User entered !!
      if (tam == 0) {
        continue;
      }
      if (sig == 1) {
        currentCommand[2] = currentCommand[1];
        currentCommand[3] = NULL;
        if (strcmp(currentCommand[0], "stop") == 0) {
          currentCommand[1] = "-SIGSTOP";
        } else {
          currentCommand[1] = "-SIGCONT";
        }
        currentCommand[0] = "kill";
      }

      int i, ok = 1;
      for (i = 1; i < tam; i++) {
        // For example sort < file.txt
        if (strcmp(currentCommand[i], "<") == 0) {
          ok = 0;
          int file = open(currentCommand[i + 1], O_RDONLY);
          if (file == -1 || currentCommand[i + 1] == NULL) {
            printf("There was an error.\n");
            exit(1);
          }
          currentCommand[i] = NULL;
          currentCommand[i + 1] = NULL;
          dup2(file, 0);
          if (execvp(currentCommand[0], currentCommand) == -1) {
            printf("Command not found.\n");
          }
          close(0);
          close(file);
          break;
        }  // For example ls -ls > file.txt
        else if (strcmp(currentCommand[i], ">") == 0) {
          ok = 0;
          int file = open(currentCommand[i + 1], O_WRONLY | O_CREAT, 0644);
          if (file == -1 || currentCommand[i + 1] == NULL) {
            printf("There was an error.\n");
            exit(1);
          }
          currentCommand[i] = NULL;
          currentCommand[i + 1] = NULL;
          dup2(file, 1);
          if (execvp(currentCommand[0], currentCommand) == -1) {
            printf("Command not found.\n");
          }
          close(1);
          close(file);
          break;
        }  // For example ls -ls | sort
        else if (strcmp(currentCommand[i], "|") == 0) {
          ok = 0;
          char *first[i + 1];
          char *second[tam - i];
          int j;
          for (j = 0; j < i; j++) {
            first[j] = currentCommand[j];
          }
          int k;
          for (k = 0; k < tam - i - 1; k++) {
            second[k] = currentCommand[k + i + 1];
          }
          second[tam - i - 1] = NULL;
          first[i] = NULL;

          int p[2];
          if (pipe(p) == -1) {
            printf("There was an error.\n");
            exit(1);
          }
          int PID2;
          if ((PID2 = fork()) > 0) {
            wait(NULL);
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            if (execvp(second[0], second) == -1) {
              printf("Command not found.\n");
            }
          } else if (PID2 == 0) {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            if (execvp(first[0], first) == -1) {
              printf("Command not found.\n");
            }
          }
          break;
        }
      }
      if (ok == 1) {
        if (execvp(currentCommand[0], currentCommand) == -1) {
          printf("Command not found.\n");
        }
      }
      exit(1);
    } else if (PID > 0) {
      if (amp == 0) {
        wait(NULL);
      }
    } else {
      printf("There was an error.\n");
    }
  }
  return 0;
}