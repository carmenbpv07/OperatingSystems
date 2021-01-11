#include <asm/param.h>
#include <linux/gcd.h>
#include <linux/hash.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>

/** Chapter 2: Operating-System Structures
    Programming Projects P-4
    Exercise 2:
      To compile this file: make
      To load the new kernel module: insmod exercise2.ko
      To check the kernel module: lsmod
      To check the output: dmesg
**/

int simple_init(void) {
  printk(KERN_INFO "%d\n", HZ);
  printk(KERN_INFO "%lu\n", jiffies);
  return 0;
}

void simple_exit(void) { printk(KERN_INFO "%lu\n", jiffies); }

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");