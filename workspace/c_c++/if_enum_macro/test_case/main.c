
/* main.c */

#include <stdio.h>
#include "config.h"

//#define EMPTY1
//#define EMPTY2 

int main(void)
{
	printf("%s:%d ... TURNNING_OFF = %d\r\n", __func__, __LINE__, TURNNING_OFF);
	printf("%s:%d ... POWER_GRADUALLY_TURNING = %d\r\n", __func__, __LINE__, POWER_GRADUALLY_TURNING);
	
#if EMPTY1 == EMPTY2
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#ifdef TURNNING_OFF
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#ifdef TURNNING_ON
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#ifdef POWER_GRADUALLY_TURNING
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#if TURNNING_OFF == TURNNING_ON
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#if TURNNING_OFF == 0
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif

#if 1 == POWER_GRADUALLY_TURNING
	printf("%s:%d ... here work ...\r\n", __func__, __LINE__);
#endif
	
#if TURNNING_OFF == POWER_GRADUALLY_TURNING
    printf("%s:%d ... turnning off case ...\r\n", __func__, __LINE__);
#elif TURNNING_ON == POWER_GRADUALLY_TURNING
    printf("%s:%d ... turnning on case ...\r\n", __func__, __LINE__);
#endif
    
    return 0;
}
