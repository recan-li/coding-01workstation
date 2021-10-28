
#include <stdio.h>
#include <string.h>

#include "des.h"

#define DES_TRUE                        0x01
#define DES_FALSE                       0x00
#define DES_DO_INITIAL_PERMUTATION      0x10
#define DES_ENCRYPTION_MODE             0x20
#define DES_DECRYPTION_MODE             0
#define DES_DO_FINAL_PERMUTATION        0x40
#define DES_ENCRYPT_BLOCK               (DES_DO_INITIAL_PERMUTATION|DES_ENCRYPTION_MODE|DES_DO_FINAL_PERMUTATION)
#define DES_DECRYPT_BLOCK               (DES_DO_INITIAL_PERMUTATION|DES_DECRYPTION_MODE|DES_DO_FINAL_PERMUTATION)

const uint8_t IPP[64] = {
    57, 49, 41, 33, 25, 17, 9, 1,  59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7,
    56, 48, 40, 32, 24, 16, 8, 0,  58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,  62, 54, 46, 38, 30, 22, 14, 6
};

const uint8_t IPN[64] = {
    39, 7, 47, 15, 55, 23, 63, 31,  38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,  36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,  34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25,  32, 0, 40, 8, 48, 16, 56, 24
}; //Inverse permutation

const uint8_t Choose56[56] = {
    56, 48, 40, 32, 24, 16, 8,  0, 57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 60, 52, 44, 36,
    28, 20, 12, 4, 27, 19, 11, 3
}; //Choosing the 56bit key from 64bit

const uint8_t key_round[32] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
    0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
}; //shift key left //shift key right

const uint8_t Choose48[48] = {
    31, 0, 1, 2, 3, 4, 3, 4,   5, 6, 7, 8, 7, 8, 9, 10,
    11, 12, 11, 12, 13, 14, 15, 16,  15, 16, 17, 18, 19, 20, 19, 20,
    21, 22, 23, 24, 23, 24, 25, 26,  27, 28, 27, 28, 29, 30, 31, 0
}; //expands the right half text of 32 bits to 48 bits

const uint8_t E[48] = {
    13, 16, 10, 23, 0, 4, 2, 27,  14, 5, 20, 9, 22, 18, 11, 3,
    25, 7, 15, 6, 26, 19, 12, 1,  40, 51, 30, 36, 46, 54, 29, 39,
    50, 44, 32, 47, 43, 48, 38, 55,  33, 52, 45, 41, 49, 35, 28, 31
}; //Compression and permutation for key

const uint8_t PP[32] = {
    15, 6, 19, 20, 28, 11, 27, 16,  0 , 14, 22, 25, 4, 17, 30, 9,
    1, 7, 23, 13, 31, 26, 2, 8,  18, 12, 29, 5, 21, 10, 3, 24
}; //P-box permutation

const uint8_t S[8][64] = {{
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    },
    {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    },
    {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    },
    {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    },
    {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    },
    {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    },
    {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    },
    {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    }
};

const uint8_t _bitposition[8] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

static void check_table(uint8_t line, uint8_t *text, uint8_t *lasttext, const uint8_t *IDD)
{
    uint8_t i, j, k, temp, temp2;

    for (j = 0, k = 0; j < line; j++, k += 8) {
        lasttext[j] = 0;
        for (i = 0; i < 8; i++) {
            temp2 = IDD[k + i];
            temp = text[temp2 / 8]; // get the byte
            temp &= _bitposition[temp2 & 0x7]; // get the bit
            if (temp) {
                lasttext[j] |= _bitposition[i];
            }
        }
    }
}

static void single_des_operation(uint8_t *plaintext, uint8_t *key, uint8_t mode)
{
    static uint8_t prevtext[8];
    uint8_t prevkey[8], Ltext[4], Rtext[4];
    char temp, temp1;
    int32_t i = 0;
    int32_t Round = 0;
    uint8_t j = 0;
    
    if (mode & DES_DO_INITIAL_PERMUTATION) {
        check_table(8, plaintext, prevtext, IPP); //Initial permutation
    }

    for (i = 0; i < 4; i++) {
        Ltext[i] = prevtext[i];
        Rtext[i] = prevtext[i + 4];
    }

    check_table(7, key, prevkey, Choose56);

    for (Round = 0; Round < 16; Round++) {
        //rotate both 28bits block to left(encrypt) or right(decrypt)
        if (mode & DES_ENCRYPTION_MODE) { // encrypt
            for (j = 0; j < key_round[Round]; j++) {
                temp = prevkey[3] & 0x08;
                for (i = 7; i > 0; i--) {
                    temp1 = prevkey[i - 1] & 0x80;
                    prevkey[i - 1] <<= 1;
                    if (temp) {
                        prevkey[i - 1] |= 0x01;
                    }
                    temp = temp1;
                }

                if (temp) {
                    prevkey[3] |= 0x10;
                } else {
                    prevkey[3] &= 0xEF;
                }
            }
        } else { // decrypt
            for (j = 0; j < key_round[Round + 16]; j++) {
                temp = prevkey[3] & 0x10;
                for (i = 0; i < 7; i++) {
                    temp1 = prevkey[i] & 0x01;
                    prevkey[i] >>= 1;
                    if (temp) {
                        prevkey[i] |= 0x80;
                    }
                    temp = temp1;
                }

                if (temp) {
                    prevkey[3] |= 0x08;
                } else {
                    prevkey[3] &= 0xF7;
                }
            }
        }

        check_table(6, prevkey, plaintext, E); //Compression permutation
        check_table(6, Rtext, prevtext, Choose48); //Expansion permutation

        //Expanded right half xor_operation with the subkey
        prevtext[0] ^= plaintext[0];
        prevtext[1] ^= plaintext[1];
        prevtext[2] ^= plaintext[2];
        prevtext[3] ^= plaintext[3];
        prevtext[4] ^= plaintext[4];
        prevtext[5] ^= plaintext[5];

        for (j = 6, i = 8; j > 0; j -= 3, i -= 4) { //S-Box Substitution
            plaintext[i - 1] = prevtext[j - 1];
            plaintext[i - 2] = ((prevtext[j - 1] >> 6) & 0x03) | (prevtext[j - 2] << 2);
            plaintext[i - 3] = ((prevtext[j - 2] >> 4) & 0x0f) | (prevtext[j - 3] << 4);
            plaintext[i - 4] = prevtext[j - 3] >> 2;
        }

        for (i = 0; i < 8; i++) { //Get the S-Box location
            temp = plaintext[i] & 0x21;
            if (temp & 0x01) {
                temp = (temp & 0x20) | 0x10;
            }
            plaintext[i] = temp | ((plaintext[i] >> 1) & 0x0F);
        }

        //Get S-Box output
        plaintext[0] = S[0][plaintext[0]];
        plaintext[1] = S[1][plaintext[1]];
        plaintext[2] = S[2][plaintext[2]];
        plaintext[3] = S[3][plaintext[3]];
        plaintext[4] = S[4][plaintext[4]];
        plaintext[5] = S[5][plaintext[5]];
        plaintext[6] = S[6][plaintext[6]];
        plaintext[7] = S[7][plaintext[7]];

        //Combine 4-bit block to form 32-bit block
        plaintext[0] = (plaintext[0] << 4) | plaintext[1];
        plaintext[1] = (plaintext[2] << 4) | plaintext[3];
        plaintext[2] = (plaintext[4] << 4) | plaintext[5];
        plaintext[3] = (plaintext[6] << 4) | plaintext[7];

        check_table(4, plaintext, prevtext, PP);

        for (i = 0; i < 4; i++) {
            prevtext[i] ^= Ltext[i];
            Ltext[i] = Rtext[i];
            Rtext[i] = prevtext[i];
        }
    }

    for (i = 0; i < 4; i++) {
        prevtext[i] = Rtext[i];
        prevtext[i + 4] = Ltext[i];
    }

    if (mode & DES_DO_FINAL_PERMUTATION) {
        check_table(8, prevtext, plaintext, IPN); //Final permutation
    }
}

static int32_t xor_operation(uint8_t *out, const uint8_t *data1, const uint8_t *data2, uint32_t dwLen)
{
    int32_t ret = DES_TRUE;
    uint32_t i = 0;

    if ((dwLen != 0) && ((data1 == NULL) || (data2 == NULL) || (out == NULL))) {
        ret = DES_FALSE;
    } else {
        for (i = 0; i < dwLen; i++) {
            out[i] = data1[i] ^ data2[i];
        }
    }
    return ret;
}

int32_t crypto_des_encrypt(const uint8_t *data, uint32_t data_len, uint8_t *out, const uint8_t *iv,
                           const uint8_t *key, uint32_t key_len, des_mode_e mode)
{
    uint32_t i = 0;

    if ((data_len % DES_BLOCK_LEN != 0) || \
            ((key_len != DES_KEY_LEN_8) && \
            (key_len != DES_KEY_LEN_16) && \
            (key_len != DES_KEY_LEN_24))) {
        return -1;
    }

    for (i = 0; i < data_len / DES_BLOCK_LEN; i++) {
        if (mode == DES_MODE_CBC) {
            if (i > 0) {
                xor_operation(&out[i * DES_BLOCK_LEN], &data[i * DES_BLOCK_LEN], \
                    &out[(i - 1) * DES_BLOCK_LEN], DES_BLOCK_LEN);
            } else {
                xor_operation(&out[i], &data[i], iv, DES_BLOCK_LEN);
            }
        } else {
            memcpy(&out[i * DES_BLOCK_LEN], &data[i * DES_BLOCK_LEN], DES_BLOCK_LEN);
        }

        if (key_len == DES_KEY_LEN_8) { //Single DES
            single_des_operation(&out[i * DES_BLOCK_LEN], (uint8_t *)&key[0], DES_ENCRYPT_BLOCK);
        } else { //Trip DES
            uint8_t *key1 = (uint8_t *)&key[0];
            uint8_t *key2 = (uint8_t *)&key[DES_KEY_LEN_8];
            uint8_t *key3 = (uint8_t *)&key[0];

            if (key_len == DES_KEY_LEN_24) {
                key3 = (uint8_t *)&key[DES_KEY_LEN_16];
            }
            single_des_operation(&out[i * DES_BLOCK_LEN], key1, DES_ENCRYPT_BLOCK);
            single_des_operation(&out[i * DES_BLOCK_LEN], key2, DES_DECRYPT_BLOCK);
            single_des_operation(&out[i * DES_BLOCK_LEN], key3, DES_ENCRYPT_BLOCK);
        }
    }

    return 0;
}

int32_t crypto_des_decrypt(const uint8_t *data, uint32_t data_len, uint8_t *out, const uint8_t *iv,
                            const uint8_t *key, uint32_t key_len, des_mode_e mode)
{
    int32_t i = 0;

    if ((data_len % DES_BLOCK_LEN != 0) || \
            ((key_len != DES_KEY_LEN_8) && \
            (key_len != DES_KEY_LEN_16) && \
            (key_len != DES_KEY_LEN_24))) {
        return -1;
    }

    for (i = data_len / DES_BLOCK_LEN - 1; i >= 0; i--) {
        memcpy(&out[i * DES_BLOCK_LEN], &data[i * DES_BLOCK_LEN], DES_BLOCK_LEN);
        if (key_len == DES_KEY_LEN_8) { //Single DES            
            single_des_operation(&out[i * DES_BLOCK_LEN], (uint8_t *)&key[0], DES_DECRYPT_BLOCK);
        } else { //Trip DES
            uint8_t *key1 = (uint8_t *)&key[0];
            uint8_t *key2 = (uint8_t *)&key[DES_KEY_LEN_8];
            uint8_t *key3 = (uint8_t *)&key[0];

            if (key_len == DES_KEY_LEN_24) {
                key3 = (uint8_t *)&key[DES_KEY_LEN_16];
            }
            single_des_operation(&out[i * DES_BLOCK_LEN], key3, DES_DECRYPT_BLOCK);
            single_des_operation(&out[i * DES_BLOCK_LEN], key2, DES_ENCRYPT_BLOCK);
            single_des_operation(&out[i * DES_BLOCK_LEN], key1, DES_DECRYPT_BLOCK);
        }

        if (mode == DES_MODE_CBC) {
            if (i > 0) {
                xor_operation(&out[i * DES_BLOCK_LEN], &out[i * DES_BLOCK_LEN], \
                    &data[(i - 1) * DES_BLOCK_LEN], DES_BLOCK_LEN);
            } else {
                xor_operation(&out[i], &out[i], iv, DES_BLOCK_LEN);
            }
        }
    }

    return 0;
}
