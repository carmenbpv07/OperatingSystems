#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

/** Shortest-job-first (SJF): schedules tasks in order of the length of the
                              tasks’ next CPU burst.
    To compile: make sjf
    To execute: ./sjf schedule.txt
**/

struct node *taskList = NULL;

// add a task to the list
void add(char *name, int priority, int burst) {
  Task *t = malloc(sizeof(Task));  // t->new task to insert
  t->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(t->name, name);
  t->priority = priority;
  t->burst = burst;
  insert(&taskList, t);  // void insert(struct node **head, Task *newTask)
}

Task *pickNextTask() {
  struct node *my_node = taskList;  // starting with the head node
  Task *shortest_job = taskList->task;
  while (my_node) {
    if (my_node->task->burst <= shortest_job->burst) {
      shortest_job = my_node->task;
    }
    my_node = my_node->next;
  }
  return shortest_job;  // returns the task with the shortest CPU burst
}

// invoke the scheduler
void schedule() {
  while (taskList) {
    Task *t = pickNextTask();
    run(t, t->burst);  // void run(Task *task, int slice) prints the information
                       // of the task
    delete (&taskList, t);  // void delete (struct node **head, Task *task)
  }
}