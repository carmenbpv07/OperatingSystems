#ifndef TASK_H
#define TASK_H

/**
    Representation of a task in the system.
**/

// Representation of a task
typedef struct task {
  char *name;
  int tid;
  int priority;
  int burst;
  int remaining_burst;
} Task;

#endif
