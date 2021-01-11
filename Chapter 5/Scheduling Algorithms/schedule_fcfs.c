#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

/**
    First-come, first-served (FCFS): schedules tasks in the order in which
                                    they request the CPU.
    To compile: make fcfs
    To execute: ./fcfs schedule.txt
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
  struct node *lastNode = taskList;  // starting with the head node
  while (lastNode->next) {
    lastNode = lastNode->next;
  }
  return lastNode->task;  // returns the last node in the linked list
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