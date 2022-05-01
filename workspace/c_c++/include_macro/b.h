
/* b.h */

#ifndef __B_H__
#define __B_H__

#include "a.h"

typedef enum _device_mode_e {
	I2C_MODE = 0,
	PWM_MODE = 1,
} device_mode_e;

/* slelect I2C_MODE */
#ifndef PROJECT_DEVICE_MODE
#define PROJECT_DEVICE_MODE  I2C_MODE
#endif

extern int test_b;

#endif /* __B_H__ */
