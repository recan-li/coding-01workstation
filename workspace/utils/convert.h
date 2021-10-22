
#ifndef __CONVERT_H__
#define __CONVERT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

#define UTILS_ERR   -1
#define UTILS_OK    0

extern int32_t utils_hex_string_2_bytes(const char *hextring, uint8_t *bytes, uint16_t *length);

extern int32_t utils_bytes_2_hex_string(const uint8_t *bytes, uint16_t length, char *hextring);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__CONVERT_H__*/
