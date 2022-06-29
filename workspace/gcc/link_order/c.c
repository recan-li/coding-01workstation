
#include <stdio.h>

extern void func_d(void);

void func_c(void)
{
	printf("This is %s in [%s] !\r\n", __func__, __FILE__);

	/* call function d */
	func_d();
}