
#include <stdio.h>

extern void func_f(void);

void func_e(void)
{
	printf("This is %s in [%s] (static library) !\r\n", __func__, __FILE__);

	/* call function f */
	func_f();
}
