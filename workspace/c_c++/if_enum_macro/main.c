
#include <stdio.h>

#if MACRO_DEFINE_EN //macro
#define TRUN_ON 			1
#define TRUN_OFF 			0
#else //enum
typedef enum {
	TRUN_OFF,
	TRUN_ON,
} trun_on_off_e;
#endif

#define APP_CONFIG_SELECT 	TRUN_ON

int main(int argc, const char *argv[])
{
	printf("Hello world !\n");
	printf("TRUN_ON: %d\n", TRUN_ON);
	printf("TRUN_OFF: %d\n", TRUN_OFF);
	printf("APP_CONFIG_SELECT: %d\n", APP_CONFIG_SELECT);

#if (TRUN_OFF == APP_CONFIG_SELECT)
	#warning "warning here 111"
	printf("do something here 111 (off) ...\n");
#else
	#warning "warning here 222"
	printf("do other things here 222 (on) ...\n");
#endif

	return 0;
}