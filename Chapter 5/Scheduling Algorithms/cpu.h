#ifndef CPU_H
#define CPU_H

#include "task.h"
// Length of a time quantum
#define QUANTUM 10

// Run the specified task for the following time slice
void run(Task *task, int slice);

#endif