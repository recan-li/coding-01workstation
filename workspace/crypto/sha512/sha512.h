
#ifndef __SHA512_H__
#define __SHA512_H__

#include <stdint.h>

#define SHA512_DIGEST_LEN 64         	// SHA512 outputs a 64 byte digest

typedef struct _sha512_ctx_t {
	uint64_t 	total[2];          		/*!< number of bytes processed  */
    uint64_t 	state[8];          		/*!< intermediate digest state  */
    uint8_t 	buffer[128];  			/*!< data block being processed */
    int32_t		is_384;             	/*!< 0 => SHA-512, else SHA-384 */
} sha512_ctx_t;

void crypto_sha512_init(sha512_ctx_t *ctx);
void crypto_sha512_update(sha512_ctx_t *ctx, const uint8_t *data, uint32_t len);
void crypto_sha512_final(sha512_ctx_t *ctx, uint8_t *digest);

#endif   // __SHA512_H__
