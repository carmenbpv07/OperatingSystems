#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

/**
    Round-robin (RR) scheduling: each task is run for a time quantum
                                 (or for the remainder of its CPU burst).
    To compile: make rr
    To execute: ./rr schedule.txt
**/

struct node *taskList = NULL;
struct node *current_node;

// add a task to the list
void add(char *name, int priority, int burst) {
  Task *t = malloc(sizeof(Task));  // t->new task to insert
  t->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(t->name, name);
  t->priority = priority;
  t->burst = burst;
  t->remaining_burst = burst;
  insert(&taskList, t);  // void insert(struct node **head, Task *newTask)
}

Task *pickNextTask() {
  Task *current_task = current_node->task;
  if (!current_node->next) {
    current_node = taskList;
  } else {
    current_node = current_node->next;
  }
  return current_task;
}

// invoke the scheduler
void schedule() {
  current_node = taskList;
  while (taskList) {
    Task *t = pickNextTask();
    int current_burst = t->remaining_burst - QUANTUM;
    if (current_burst <= 0) {
      current_burst = t->remaining_burst;
      delete (&taskList, t);
    } else {
      current_burst = QUANTUM;
      t->remaining_burst -= QUANTUM;
    }
    run(t, current_burst);
  }
}