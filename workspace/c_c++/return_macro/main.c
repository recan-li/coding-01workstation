
#include <stdio.h>

/* always return 1 */
#define RETURN_MACRO()			({do {} while(0);1;})
#define RETURN_MACRO2()			1

/* return a+b */
#define A_PLUS_B_MACRO(a, b)	({int ret; ret = (a) + (b); ret;})
#define A_PLUS_B_MACRO2(a, b)	({int ret; ret = add((a), (b)); ret;})

int add(int a, int b)
{
	return (a + b);
}

int main(int argc, const char *argv[])
{
	int a = 6;
	int b = 7;

	printf("Hello world !\n");
	printf("RETURN_MACRO: %d\n", RETURN_MACRO());
	printf("RETURN_MACRO2: %d\n", RETURN_MACRO2());
	printf("a + b = %d\n", A_PLUS_B_MACRO(a, b));
	printf("a + b = %d\n", A_PLUS_B_MACRO2(a, b));

	return 0;
}