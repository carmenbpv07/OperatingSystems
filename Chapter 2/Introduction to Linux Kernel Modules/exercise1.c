#include <linux/gcd.h>
#include <linux/hash.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/** Chapter 2: Operating-System Structures
    Programming Projects P-4
    Exercise 1:
      To compile this file: make
      To load the new kernel module: insmod exercise1.ko
      To check the kernel module: lsmod
      To check the output: dmesg 
**/

int simple_init(void) {
  printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
  return 0;
}

void simple_exit(void) { printk(KERN_INFO "%lu\n", gcd(3300, 24)); }

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");