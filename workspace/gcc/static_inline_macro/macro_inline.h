#ifndef __MACRO_INLINE_H__
#define __MACRO_INLINE_H__

FORCE_FUNCTION static inline void test_macro_inline(void)
{
	int a = 1;
	int b = 1;

	b = test_macro() + a;

	printf("b: %d\n", b);
}

#endif /* __MACRO_INLINE_H__ */