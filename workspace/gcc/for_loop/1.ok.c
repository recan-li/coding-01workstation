
#include <stdio.h>
#include <stdint.h>

#include "2.h" //包含checksum的头文件

typedef struct _data_t {
    /* result, final result */
    uint8_t len;
    uint8_t flag;
    uint8_t passwd_len; 
    uint8_t *passwd; 
    uint8_t ssid_len; 
    uint8_t *ssid; 
    uint8_t token_len; 
    uint8_t *token; 
    uint8_t bssid_type_len; 
    uint8_t *bssid; 
    uint8_t ssid_is_gbk;
    uint8_t ssid_auto_complete_disable;
    uint8_t data[127];
    uint8_t checksum;
} data_t;

static data_t g_data;

void set_global_data(void)
{
	g_data.len = 100;
	printf("%s:%d ...len=%d\n", __func__, __LINE__, g_data.len);
	g_data.len = 0;
	printf("%s:%d ...len=%d\n", __func__, __LINE__, g_data.len);
}

int main(int argc, const char *argv[])
{
	uint16_t res;

	printf("%s:%d ...\n", __func__, __LINE__);
	set_global_data();
	res = checksum(&g_data.data[0], g_data.len - 1);
	printf("%s:%d ... res: 0x%04x\n", __func__, __LINE__, res);

	return 0;
}