
/* main.c */

#include <stdio.h>
//#include "b.h"
//#include "a.h"
#include "c.h"

int main(void)
{
	printf("project device mode : %d (0:I2C  1:PWM)\r\n", LIGHT_DEVICE_MODE);
    
    return 0;
}
