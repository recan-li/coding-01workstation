
/* a.h */

#ifndef __A_H__
#define __A_H__

#include "b.h"

#ifndef PROJECT_DEVICE_MODE
//QWQQQ (compile here ...)
#define PROJECT_DEVICE_MODE PWM_MODE
#endif

#define LIGHT_DEVICE_MODE 	PROJECT_DEVICE_MODE

extern int test_a;

#endif /* __A_H__ */
