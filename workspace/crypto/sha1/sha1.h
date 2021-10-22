
#ifndef __SHA1_H__
#define __SHA1_H__

#include <stdint.h>

#define SHA1_DIGEST_LEN 20         	// SHA1 outputs a 20 byte digest

typedef struct _sha1_ctx_t {
    uint32_t 		total[2];     	/*!< number of bytes processed  */
    uint32_t 		state[5];   	/*!< intermediate digest state  */
    uint8_t 		buffer[64];   	/*!< data block being processed */
} sha1_ctx_t;

void crypto_sha1_init(sha1_ctx_t *ctx);
void crypto_sha1_update(sha1_ctx_t *ctx, const uint8_t *data, uint32_t len);
void crypto_sha1_final(sha1_ctx_t *ctx, uint8_t *digest);

#endif   // __SHA1_H__
