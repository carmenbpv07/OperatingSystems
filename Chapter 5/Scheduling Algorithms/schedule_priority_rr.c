#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

/**
    Priority with round-robin: schedules tasks in order of priority and
                               uses round-robin scheduling for tasks with
                               equal priority.
    To compile: make priority_rr
    To execute: ./priority_rr schedule.txt
**/

struct node *taskList[MAX_PRIORITY + 1];
struct node *current_node;

// add a task to the list
void add(char *name, int priority, int burst) {
  Task *t = malloc(sizeof(Task));  // t->new task to insert
  t->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(t->name, name);
  t->priority = priority;
  t->burst = burst;
  t->remaining_burst = burst;
  insert(&taskList[priority],
         t);  // void insert(struct node **head, Task *newTask)
}

Task *pickNextTask(struct node *t) {
  Task *current_task = current_node->task;
  if (!current_node->next) {
    current_node = t;
  } else {
    current_node = current_node->next;
  }
  return current_task;
}

// invoke the scheduler
void schedule() {
  int i;
  for (i = MAX_PRIORITY; i >= MIN_PRIORITY; i--) {
    current_node = taskList[i];
    while (taskList[i]) {
      Task *t = pickNextTask(taskList[i]);
      int current_burst = t->remaining_burst - QUANTUM;
      if (current_burst <= 0) {
        current_burst = t->remaining_burst;
        delete (&taskList[i], t);
      } else {
        current_burst = QUANTUM;
        t->remaining_burst -= QUANTUM;
      }
      run(t, current_burst);
    }
  }
}