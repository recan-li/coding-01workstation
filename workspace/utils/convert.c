
#include <string.h>
#include <stdint.h>
#include <string.h>

#include "convert.h"

typedef struct _byte_t {
    uint8_t low:    4;
    uint8_t high:   4;
} byte_t;

int utils_hex_string_2_bytes(const char *hextring, uint8_t *bytes, uint16_t *length)
{
    const char *p = hextring;
    byte_t tmp;
    uint16_t cnt = 0;

    if ((hextring == NULL) || (bytes == NULL) || (length == NULL)) {
        return UTILS_ERR;
    }

    *length = 0;
    if ((strlen(p) % 2) != 0) {
        return UTILS_ERR;
    }

    while (*p != '\0') {
        if ((*p >= '0') && (*p <= '9'))
            tmp.high = *p - '0';
        else if ((*p >= 'A') && (*p <= 'F'))
            tmp.high = *p - 'A' + 10;
        else if ((*p >= 'a') && (*p <= 'f'))
            tmp.high = *p - 'a' + 10;
        else {
            return UTILS_ERR;
        }
        p++;
        if ((*p >= '0') && (*p <= '9'))
            tmp.low = *p - '0';
        else if ((*p >= 'A') && (*p <= 'F'))
            tmp.low = *p - 'A' + 10;
        else if ((*p >= 'a') && (*p <= 'f'))
            tmp.low = *p - 'a' + 10;
        else {
            return UTILS_ERR;
        }
        p++;
        bytes[cnt++] = *(uint8_t * ) & tmp;
    }

    *length = cnt;

    return UTILS_OK;
}

int utils_bytes_2_hex_string(const uint8_t *bytes, uint16_t length, char *hextring)
{
    uint16_t i = 0, cnt = 0;
    byte_t tmp;
    
    if ((bytes == NULL) || (hextring == NULL)) {
        return UTILS_ERR;
    }

    while (i < length) {
        tmp = *(byte_t * ) & bytes[i++];
        if (tmp.high <= 9)
            hextring[cnt++] = tmp.high + '0';
        else
            hextring[cnt++] = tmp.high - 10 + 'A';

        if (tmp.low <= 9)
            hextring[cnt++] = tmp.low + '0';
        else
            hextring[cnt++] = tmp.low - 10 + 'A';
    }

    hextring[cnt] = '\0';

    return UTILS_OK;
}
