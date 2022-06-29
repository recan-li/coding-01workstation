
#include <stdio.h>

extern void func_d_new(void);

void func_f(void)
{
	printf("This is %s in [%s] (static library) !\r\n", __func__, __FILE__);

	/* call function d new */
	func_d_new();
}