
#include <stdio.h>

#include "sub.h"

#ifdef USED_FUNC
void used_func(void)
{
	printf("This is a used function !\n");
}
#endif

int main(int argc, const char *argv[])
{
	printf("Hello world !\n");
	printf("TEST_NUM = %d\n", TEST_NUM);
	printf("sub_func() = %d\n", sub_func(1));

#ifdef USED_FUNC
	used_func();
#endif

	return 0;
}