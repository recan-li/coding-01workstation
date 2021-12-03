
#include <stdio.h>

/* This include order is very important ! */
#ifdef ERROR_CASE
#include "macro_inline.h"
#include "macro.h"
#else // OK CASE
#include "macro.h"
#include "macro_inline.h"
#endif

#if 0
/* only inline function : link error ! */
inline void test_func(int a, int b)
{
	printf("%d, %d\n", a, b);
}
#endif

/* normal function: OK */
void test_func1(int a, int b)
{
	printf("%d, %d\n", a, b);
}

/* static function: OK */
static void test_func2(int a, int b)
{
	printf("%d, %d\n", a, b);
}

/* static inline function: OK, but no real inline */
static inline void test_func3(int a, int b)
{
	printf("%d, %d\n", a, b);
}

/* static inline function: OK, it real inline. */
FORCE_FUNCTION static inline void test_func4(int a, int b)
{
	printf("%d, %d\n", a, b);
}

int main(int argc, const char *argv[])
{
	printf("Hello world !\n");

	/* call these functions with the same input praram */
	//test_func(1, 2);
	test_func1(1, 2); // normal
	test_func2(1, 2); // static
	test_func3(1, 2); // static inline (real inline ?)
	test_func4(1, 2); // static inline (real inline ?)

	test_macro_inline();

	return 0;
}
