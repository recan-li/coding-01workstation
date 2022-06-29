
#include <stdio.h>

extern void func_b(void);

void func_a(void)
{
	printf("This is %s in [%s] !\r\n", __func__, __FILE__);
	
	/* call function b */
	func_b();
}