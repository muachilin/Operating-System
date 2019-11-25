#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{

	long a = 123;
	long b = 100;
	syscall(337);
	printf("first number is : %ld\n",a);
	printf("second number is : %ld\n",b);
	printf("multiply of two numbers : %ld\n",syscall(338,a,b));
	printf("minimum of two numbers : %ld\n",syscall(339,a,b));
	return 0;

}
