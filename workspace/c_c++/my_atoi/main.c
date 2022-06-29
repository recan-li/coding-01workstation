
#include <stdio.h>
#include <stdlib.h>

static int my_atoi(const char *nptr)
{
	int flag = 1;
	int ret = 0;
	char *p = (char *)nptr;

	while (*p == ' ') {
		p++;
	}

	if (*p == '+' || *p == '-') {
		if (*p == '-') {
			flag = -1;
		}
		p++;
	}

	while (*p != '\0') {
		if ((*p >= '0') && (*p <= '9')) {
			ret = ret * 10 + *p - '0';
			p++;
		} else {
			p++;
			break;
		}
	}

	return flag * ret;
}

static const char *test_case_list[] = 
{
	"1234",
	"-1234",
	"1234a5678",
	"-1234a5678",
	" 1234",
	"  -1234",
	"   1234a5678",
	"    -1234a5678",
	"abcd",
	"",
	"01234",
	"-01234"
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(n) sizeof(n) / sizeof(n[0])
#endif

int main(int argc, const char *argv[])
{
	int i;

	for (i = 0; i < ARRAY_SIZE(test_case_list); i++) {
		printf("atoi-%d   : [%s] => %d\r\n", i, test_case_list[i], atoi(test_case_list[i]));
		printf("my-atoi-%d: [%s] => %d\r\n", i, test_case_list[i], my_atoi(test_case_list[i]));
		printf("test-%d   : [%s]\n", i, atoi(test_case_list[i]) == my_atoi(test_case_list[i]) ? " OK " : "FAIL");
	}

	return 0;
}