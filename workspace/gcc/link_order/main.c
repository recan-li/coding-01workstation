
#include <stdio.h>

extern void func_a(void);

int main(int argc, const char *argv[])
{
	printf("This is %s in [%s] !\r\n", __func__, __FILE__);

	func_a();

	return 0;
}