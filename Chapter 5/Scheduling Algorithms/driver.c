#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "schedulers.h"
#include "task.h"

#define SIZE 100

/**
    Schedule is in the format:
      [name] [priority] [CPU burst]
**/

int main(int argc, char *argv[]) {
  FILE *in;
  char *temp;
  char task[SIZE];

  char *name;
  int priority;
  int burst;

  in = fopen(argv[1], "r");

  while (fgets(task, SIZE, in) != NULL) {
    temp = strdup(task);
    name = strsep(&temp, ",");
    priority = atoi(strsep(&temp, ","));
    burst = atoi(strsep(&temp, ","));

    // Add the task to the scheduler's list of tasks
    add(name, priority, burst);

    free(temp);
  }

  fclose(in);

  // Invoke the scheduler
  schedule();

  return 0;
}