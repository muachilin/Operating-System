#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_hello(void)
{
	printk("HELLO SYSTEM CALL b03202040 b04901009\n");
	return 0;

}

