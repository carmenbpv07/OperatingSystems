#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// Add a task to the list
void add(char *name, int priority, int burst);

// Invoke the scheduler
void schedule();
