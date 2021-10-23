
#include <string.h>
#include "sha384.h"

extern void crypto_sha384_sha512_init(sha512_ctx_t *ctx, int is_384);

/*
 * SHA-384 process init
 */
void crypto_sha384_init( sha512_ctx_t *ctx )
{
	crypto_sha384_sha512_init(ctx, 1);
}

/*
 * SHA-384 process buffer
 */
void crypto_sha384_update( sha512_ctx_t *ctx,
                               const uint8_t *data,
                               uint32_t len )
{
    crypto_sha512_update(ctx, data, len);
}

/*
 * SHA-384 final digest
 */
void crypto_sha384_final( sha512_ctx_t *ctx,
                               uint8_t *digest )
{
    crypto_sha512_final(ctx, digest);
}
