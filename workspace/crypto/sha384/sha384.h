
#ifndef __SHA384_H__
#define __SHA384_H__

#include <stdint.h>

#include "sha512.h"

typedef sha512_ctx_t sha384_ctx_t;

#define SHA384_DIGEST_LEN 48         	// SHA384 outputs a 48 byte digest

void crypto_sha384_init(sha384_ctx_t *ctx);
void crypto_sha384_update(sha384_ctx_t *ctx, const uint8_t *data, uint32_t len);
void crypto_sha384_final(sha384_ctx_t *ctx, uint8_t *digest);

#endif   // __SHA384_H__
