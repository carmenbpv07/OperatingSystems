#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

/** Chapter 3: Processes
    Programming Projects P-18
    Part II — Iterating over Tasks with a Depth-First Search Tree
      To compile this file: make
      To load the new kernel module: insmod ListingTasksDFS.ko
      To check the kernel module: lsmod
      To check the output: dmesg
**/

void dfs(struct task_struct *task) {
  printk(KERN_INFO "command : %-20s pid : %-20d state : %ld\n", task->comm,
         task->pid, task->state);
  struct task_struct *child;
  struct list_head *list;
  list_for_each(list, &task->children) {
    child = list_entry(list, struct task_struct, sibling);
    dfs(child);
  }
}

int simple_init(void) {
  printk(
      KERN_INFO
      "---Loading Kernel Module for Iterating over Tasks with a DFS tree---\n");
  printk(KERN_INFO "Listing Tasks DFS...\n");
  dfs(&init_task);
  return 0;
}

void simple_exit(void) {
  printk(KERN_INFO
         "Removing Kernel Module for Iterating over Tasks with a DFS tree\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks DFS");
MODULE_AUTHOR("SGG");
