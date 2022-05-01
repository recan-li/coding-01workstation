
/* config.h */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/* define turning on/off state */
enum {
    TURNNING_OFF 	= 1,
    TURNNING_ON		= 0,
};

/* cur configuration: select turning off */
#define POWER_GRADUALLY_TURNING TURNNING_ON

#endif /* __CONFIG_H__ */
