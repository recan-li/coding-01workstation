
#include <stdio.h>
#include <stdint.h>
#include "2.h"

uint16_t checksum(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint16_t sum = 0, res;

    printf("%d, %u\n", len, len);
    for (i = 0; i < len; i++) {
        sum += data[i];
    }

    res = sum ;
    return res;
}
