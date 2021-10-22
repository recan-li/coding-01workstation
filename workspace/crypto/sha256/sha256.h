
#ifndef __SHA256_H__
#define __SHA256_H__

#include <stdint.h>

#define SHA256_DIGEST_LEN 32         	// SHA256 outputs a 32 byte digest

typedef uint8_t 	BYTE;             	// 8-bit byte
typedef uint32_t  	WORD;             	// 32-bit word, change to "long" for 16-bit machines

typedef struct _sha256_ctx_t {
	uint8_t 			data[64];
	uint32_t 			data_len;
	unsigned long long 	bit_len;
	uint32_t 			state[8];
} sha256_ctx_t;

void crypto_sha256_init(sha256_ctx_t *ctx);
void crypto_sha256_update(sha256_ctx_t *ctx, const uint8_t *data, uint32_t len);
void crypto_sha256_final(sha256_ctx_t *ctx, uint8_t *digest);

#endif   // __SHA256_H__
