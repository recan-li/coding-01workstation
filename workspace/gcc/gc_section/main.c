
#include <stdio.h>

#define CODE_SECTION(x)           	__attribute__((section(x)))
#define CODE_KEEP_USED				CODE_SECTION(".text.keep.used.code")

void unused_func1(int a)
{
	printf("a: %d\n", a);
}

CODE_KEEP_USED void unused_func2(int a)
{
	printf("a: %d\n", a);
}

int main(int argc, const char *argv[])
{
	printf("Hello world !\n");
	return 0;
}