#ifndef __DES_H__
#define __DES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

#define DES_BLOCK_LEN 		8       // 8bytes

#define DES_KEY_LEN_8		8		// key-length: 8bytes  -> single DES
#define DES_KEY_LEN_16		16      // key-length: 16bytes -> triple DES (key1=key[0], key2=key[8], key3=key[0])
#define DES_KEY_LEN_24		24		// key-length: 24bytes -> triple DES (key1=key[0], key2=key[8], key3=key[16])

typedef enum _des_mode_e {
	DES_MODE_ECB,
	DES_MODE_CBC
} des_mode_e;

int32_t crypto_des_encrypt(const uint8_t *data, uint32_t data_len, uint8_t *out, const uint8_t *iv,
                           const uint8_t *key, uint32_t key_len, des_mode_e mode);
int32_t crypto_des_decrypt(const uint8_t *data, uint32_t data_len, uint8_t *out, const uint8_t *iv,
                            const uint8_t *key, uint32_t key_len, des_mode_e mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__DES_H__*/
