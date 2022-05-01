#include <stdio.h>
#include <assert.h>

char *_memmove(char* dest, const char *src, size_t len)
{
    assert(dest && src && (len > 0));
	
	if (dest == src) {
		;
	} else if (dest <= src || (char *)dest >= ((char *)src + len)) {
        char *p = dest;
		int i;
		/* The same as memcpy */
        for (i = 0; i < len; i++) {
            *p++ = *src++;
		}
    } else if (dest > src) {
        char *p = dest + len - 1;
        src += len - 1;
		int i;
		/* Copy data from back to front */
        for (i = len - 1; i >= 0; i--) {
            *p-- = *src--;
		}
    }

    return dest;
}

char *_memcopy(char* dest, const char *src, size_t len)
{
    assert(dest && src && (len > 0));
	
	if (dest == src) {
		;
	} else {
        char *p = dest;
		size_t i;
        for (i = 0; i < len; i++) {
            *p++ = *src++;
		}
    } 

    return dest;
}

int main(void)
{
    char buf[30] = "123456789abcdef";
	
	printf("before-memmove-buf: %s\r\n", buf);
    _memmove(buf + 5, buf, 3);
	printf("after-memmove-buf: %s\r\n", buf);
	printf("before-memcpy-buf: %s\r\n", buf);
    _memcopy(buf + 5, buf, 3);
	printf("after-memcpy-buf: %s\r\n", buf);

	printf("before-memmove-buf: %s\r\n", buf);
    _memmove(buf + 5, buf, 9);
	printf("after-memmove-buf: %s\r\n", buf);
	printf("before-memcpy-buf: %s\r\n", buf);
    _memcopy(buf + 5, buf, 9);
	printf("after-memcpy-buf: %s\r\n", buf);

	return 0;
}
