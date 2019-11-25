#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_min(long a,long b)
{
	if (a < b){return a;}
	else{return b;}
}
