
#include <stdio.h>

inline void test_func(int a, int b)
{
	printf("%d, %d\n", a, b);
}

int main(int argc, const char *argv[])
{
	printf("Hello world !\n");
	test_func(1, 2);
	return 0;
}