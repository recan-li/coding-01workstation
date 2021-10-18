
#ifndef __MD5_H__
#define __MD5_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

typedef struct _md5_ctx_t {
    uint32_t                count[2];
    uint32_t                state[4];
    uint8_t                 buffer[64];
} md5_ctx_t;

#define F(x,y,z)            ((x & y) | (~x & z))
#define G(x,y,z)            ((x & z) | (y & ~z))
#define H(x,y,z)            (x^y^z)
#define I(x,y,z)            (y ^ (x | ~z))
#define ROTATE_LEFT(x,n)    ((x << n) | (x >> (32-n)))

#define MD5_DIGEST_LEN      16

#define FF(a,b,c,d,x,s,ac) \
{ \
        a += F(b,c,d) + x + ac; \
        a = ROTATE_LEFT(a,s); \
        a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
        a += G(b,c,d) + x + ac; \
        a = ROTATE_LEFT(a,s); \
        a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
        a += H(b,c,d) + x + ac; \
        a = ROTATE_LEFT(a,s); \
        a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
        a += I(b,c,d) + x + ac; \
        a = ROTATE_LEFT(a,s); \
        a += b; \
}

extern void crypto_md5_init(md5_ctx_t *ctx);
extern void crypto_md5_update(md5_ctx_t *ctx, uint8_t *in, uint32_t in_len);
extern void crypto_md5_final(md5_ctx_t *ctx, uint8_t digest[MD5_DIGEST_LEN]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__MD5_H__*/
