
#include <stdio.h>
#include <string.h>

#include "des.h"
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

typedef struct _des_test_data_t {
    const char *name;
    const char *data;
    const char *cipher_exp;
    const char *key;
    const char *iv;
    int         mode;
} des_test_data_t;

static des_test_data_t g_des_test_data[] = 
{
    {
        "DES_8-ECB-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "5D9D966FB7BD4C63C2452ADD63C75283D58253705EA8C9D2E2E69E4774C38DFF",
        "C1D0F8FB4958670D",
        "",
        DES_MODE_ECB,
    },
    {
        "DES_16-ECB-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "537B058DE0469097B657AB3639057FDE3A8AFF5D872BD02352C9785CCE9EDCA6",
        "C1D0F8FB4958670DBA40AB1F3752EF0D",
        "",
        DES_MODE_ECB,
    }, 
    {
        "DES_24-ECB-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "D7444666014085E167F20E9E6B592622CF74FB7C1F8AB3E05290C5AD81EA3140",
        "C1D0F8FB4958670DBA40AB1F3752EF0D453D784F3784E389",
        "",
        DES_MODE_ECB,
    }, 
    {
        "DES_8-CBC-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "799BFA00F4C3B2125DA1BA9185AB9B6C72940A92D7ABBDA1436F4C2C898B4D55",
        "C1D0F8FB4958670D",
        "876876DFED458693",
        DES_MODE_CBC,
    }, 
    {
        "DES_16-CBC-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "DE88B9AB8380320870E18130C306A2C953BAF27B2210EF0456B2CF90F6E2C1D3",
        "C1D0F8FB4958670DBA40AB1F3752EF0D",
        "876876DFED458693",
        DES_MODE_CBC,
    }, 
    {
        "DES_24-CBC-ENC-DEC",
        "486328584376857876876876DFED458693696994369982784325876837265867",
        "3788F49F44CFF611D1B638B0D0E71A2DB55304B3066EA2A5A864C7AC8FC111E5",
        "C1D0F8FB4958670DBA40AB1F3752EF0D453D784F3784E389",
        "876876DFED458693",
        DES_MODE_CBC,
    }, 
};

#define ARRAY_SIZE(n)   (sizeof(n)/sizeof(n[0]))

static int des_test(des_test_data_t *data)
{
    uint8_t data_hex[128];
    uint16_t data_len;
    uint8_t data_exp_hex[128];
    uint16_t data_exp_len;
    uint8_t key[24];
    uint16_t key_len;
    uint8_t iv[24];
    uint16_t iv_len;
    uint8_t data_calc[128];
    uint8_t data_calc2[128];
    int32_t ret;

    utils_hex_string_2_bytes(data->data, data_hex, &data_len);
    utils_hex_string_2_bytes(data->cipher_exp, data_exp_hex, &data_exp_len);
    utils_hex_string_2_bytes(data->key, key, &key_len);
    utils_hex_string_2_bytes(data->iv, iv, &iv_len);

    ret = crypto_des_encrypt(data_hex, data_len, data_calc, iv, key, key_len, data->mode);
    printf("DES encrypt ret: %d\n", ret);
    log_hexdump("data_hex", data_hex, data_len);
    log_hexdump("data_calc", data_calc, data_len);
    log_hexdump("iv", iv, 8);
    log_hexdump("key", key, key_len);

    if (!memcmp(data_calc, data_exp_hex, data_len)) {
        printf("DES encrypt [%s] OK !\n", data->name);
    } else {
        log_hexdump("data_exp_hex", data_exp_hex, data_len);
        log_hexdump("data_calc", data_calc, data_len);
        printf("DES encrypt [%s] FAIL !\n", data->name);
        ret = -1;
        goto exit_entry;
    }

    ret = crypto_des_decrypt(data_calc, data_len, data_calc2, iv, key, key_len, data->mode);
    printf("DES decrypt ret: %d\n", ret);
    log_hexdump("data_calc", data_calc, data_len);
    log_hexdump("data_calc2", data_calc2, data_len);
    log_hexdump("iv", iv, 8);
    log_hexdump("key", key, key_len);

    if (!memcmp(data_calc2, data_hex, data_len)) {
        printf("DES decrypt [%s] OK !\n", data->name);
    } else {
        log_hexdump("data_hex", data_hex, data_len);
        log_hexdump("data_calc2", data_calc2, data_len);
        printf("DES decrypt [%s] FAIL !\n", data->name);
        ret = -1;
        goto exit_entry;
    }

exit_entry:

    return ret;
}

int main(int argc, const char *argv[])
{
    int ret;
    int i;
    int cnt = ARRAY_SIZE(g_des_test_data);

    for (i = 0; i < cnt; i++) {        
        ret = des_test(&g_des_test_data[i]);
        if (ret < 0) {
            break;
        }
    }

	return 0;
}
