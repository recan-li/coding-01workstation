
#include <stdio.h>

#ifdef MUL_LIB_TEST

extern void func_e(void);

void func_d(void)
{
	printf("This is %s in [%s] (static library) !\r\n", __func__, __FILE__);

	/* call function e */
	func_e();
}

void func_d_new(void)
{
	printf("This is %s in [%s] (static library) !\r\n", __func__, __FILE__);
}

#else

void func_d(void)
{
	printf("This is %s in [%s] (static library) !\r\n", __func__, __FILE__);
}

#endif