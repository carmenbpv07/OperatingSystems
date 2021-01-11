#include <stdio.h>

#include "task.h"

/**
    "Virtual" CPU that also maintains track of system time.
**/

// Run this task for the specified time slice
void run(Task *task, int slice) {
  printf("Running task = [%s], priority = [%d], burst = [%d] for %d units.\n",
         task->name, task->priority, task->burst, slice);
}