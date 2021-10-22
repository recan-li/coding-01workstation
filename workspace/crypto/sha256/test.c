
#include <stdio.h>
#include <string.h>

#include "sha256.h"
#include "convert.h"

int log_hexdump(const char *title, const unsigned char *data, int len)
{
    char str[160], octet[10];
    int ofs, i, k, d;
    const unsigned char *buf = (const unsigned char *)data;
    const char dimm[] = "+------------------------------------------------------------------------------+";

    printf("%s (%d bytes):\r\n", title, len);
    printf("%s\r\n", dimm);
    printf("| Offset  : 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   0123456789ABCDEF |\r\n");
    printf("%s\r\n", dimm);

    for (ofs = 0; ofs < (int)len; ofs += 16) {
        d = snprintf( str, sizeof(str), "| %08X: ", ofs );

        for (i = 0; i < 16; i++) {
            if ((i + ofs) < (int)len) {
                snprintf( octet, sizeof(octet), "%02X ", buf[ofs + i] );
            } else {
                snprintf( octet, sizeof(octet), "   " );
            }

            d += snprintf( &str[d], sizeof(str) - d, "%s", octet );
        }
        d += snprintf( &str[d], sizeof(str) - d, "  " );
        k = d;

        for (i = 0; i < 16; i++) {
            if ((i + ofs) < (int)len) {
                str[k++] = (0x20 <= (buf[ofs + i]) &&  (buf[ofs + i]) <= 0x7E) ? buf[ofs + i] : '.';
            } else {
                str[k++] = ' ';
            }
        }

        str[k] = '\0';
        printf("%s |\r\n", str);
    }

    printf("%s\r\n", dimm);

    return 0;
}

int main(int argc, const char *argv[])
{
	const char *data = "C1D0F8FB4958670DBA40AB1F3752EF0D";
    const char *digest_exp_str = "97B7437DF061F15182974B18E62B3D8AAFE333DCBDD2074CB8D4916509B4AD23";
	uint8_t digest_calc[SHA256_DIGEST_LEN];
    uint8_t digest_exp_hex[SHA256_DIGEST_LEN];
	sha256_ctx_t ctx;
	const char *p_calc = data;
	uint8_t data_bytes[128];
	uint16_t len_bytes;
	char data_str[128];

	if (argc > 1) {
		p_calc = argv[1];
	}

	utils_hex_string_2_bytes(data, data_bytes, &len_bytes);
	log_hexdump("data_bytes", data_bytes, len_bytes);
	utils_bytes_2_hex_string(data_bytes, len_bytes, data_str);
	printf("data_str: %s\n", data_str);
	if (!strcmp(data, data_str)) {
		printf("hex string - bytes convert OK\n");
	} else {
		printf("hex string - bytes convert FAIL\n");
	}

	crypto_sha256_init(&ctx);
	crypto_sha256_update(&ctx, (uint8_t *)p_calc, strlen(p_calc));
	crypto_sha256_final(&ctx, digest_calc);

    utils_hex_string_2_bytes(digest_exp_str, digest_exp_hex, &len_bytes);
	if (len_bytes == sizeof(digest_calc) && !memcmp(digest_calc, digest_exp_hex, sizeof(digest_calc))) {
		printf("SHA256 digest test OK\n");
        log_hexdump("digest_calc", digest_calc, sizeof(digest_calc));
	} else {
		log_hexdump("digest_calc", digest_calc, sizeof(digest_calc));
		log_hexdump("digest_exp", digest_exp_hex, sizeof(digest_exp_hex));
		printf("SHA256 digest test FAIL\n");
	}

	return 0;
}
