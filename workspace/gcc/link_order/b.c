
#include <stdio.h>

extern void func_c(void);

void func_b(void)
{
	printf("This is %s in [%s] !\r\n", __func__, __FILE__);
	
	/* call function c */
	func_c();
}