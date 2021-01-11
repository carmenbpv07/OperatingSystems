#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

/**
    Various list operations
**/

// Add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
  // Add the new task to the list
  struct node *newNode = malloc(sizeof(struct node));

  newNode->task = newTask;
  newNode->next = *head;
  *head = newNode;
}

// Delete the selected task from the list
void delete (struct node **head, Task *task) {
  struct node *temp;
  struct node *prev;

  temp = *head;
  // Special case - beginning of list
  if (strcmp(task->name, temp->task->name) == 0) {
    *head = (*head)->next;
  } else {
    // Interior or last element in the list
    prev = *head;
    temp = temp->next;
    while (strcmp(task->name, temp->task->name) != 0) {
      prev = temp;
      temp = temp->next;
    }

    prev->next = temp->next;
  }
}

// Traverse the list
void traverse(struct node *head) {
  struct node *temp;
  temp = head;

  while (temp != NULL) {
    printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority,
           temp->task->burst);
    temp = temp->next;
  }
}
