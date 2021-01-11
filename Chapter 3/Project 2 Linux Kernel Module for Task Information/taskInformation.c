#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

/** Chapter 3: Processes
    Programming Projects P-15
    To compile: make
    Load module: insmod taskInformation.ko
    echo "782" > /proc/pid
    cat /proc/pid
**/

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

long pid_;

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);
ssize_t proc_write(struct file *file, char __user *usr_buf, size_t count,
                   loff_t *pos);

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
    .write = proc_write,
};

int proc_init(void) {
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);
  printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
  return 0;
}

void proc_exit(void) {
  remove_proc_entry(PROC_NAME, NULL);
  printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count,
                  loff_t *pos) {
  int rv = 0;
  char buffer[BUFFER_SIZE];
  static int completed = 0;
  if (completed) {
    completed = 0;
    return 0;
  }
  struct pid *pid_struct = find_vpid(pid_);
  struct task_struct *task = pid_task(pid_struct, PIDTYPE_PID);
  if (task) {
    rv = snprintf(buffer, BUFFER_SIZE,
                  "command = [%s], pid = [%ld], state = [%ld]\n", task->comm,
                  pid_, task->state);
  } else {
    printk(KERN_INFO "Invalid PID %ld!", pid_);
    return 0;
  }
  completed = 1;
  copy_to_user(usr_buf, buffer, rv);

  return rv;
}

ssize_t proc_write(struct file *file, char __user *usr_buf, size_t count,
                   loff_t *pos) {
  char *k_mem;
  k_mem = kmalloc(count, GFP_KERNEL);
  copy_from_user(k_mem, usr_buf, count);

  k_mem[count] = '\0';
  kstrtol(k_mem, 10, &pid_);
  printk(KERN_INFO "%s\n", k_mem);
  kfree(k_mem);
  return count;
}

/* Macros for registering module entry and exit points. */
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Task Information");
MODULE_AUTHOR("SGG");