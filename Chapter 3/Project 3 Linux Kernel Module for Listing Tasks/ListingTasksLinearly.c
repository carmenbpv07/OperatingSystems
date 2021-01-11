#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

/** Chapter 3: Processes
    Programming Projects P-17
    Part I — Iterating over Tasks Linearly
      To compile this file: make
      To load the new kernel module: insmod ListingTasksLinearly.ko
      To check the kernel module: lsmod
      To check the output: dmesg
**/

int simple_init(void) {
  printk(KERN_INFO
         "---Loading Kernel Module for Iterating over Tasks Linearly---\n");
  printk(KERN_INFO "Listing Tasks Linearly...\n");
  struct task_struct *task = NULL;
  for_each_process(task) {
    printk(KERN_INFO "command : %-20s pid : %-20d state : %ld\n", task->comm,
           task->pid, task->state);
  }
  return 0;
}

void simple_exit(void) {
  printk(KERN_INFO
         "Removing Kernel Module for Iterating over Tasks Linearly\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks Linearly");
MODULE_AUTHOR("SGG");
