#include "base64_encode.h"
#include "common.h"

#if __has_include("password_config.local.h")
#include "password_config.local.h"
#endif

#define BASE64_DEFAULT_TABLE_BODY                                              \
  "ABCDEfGhiJKlMnopqrsTUVWxyz"                                                 \
  "!$%^&*()[]{}_-=:@;',.<>?|~"                                                 \
  "0123456789"                                                                 \
  "+/"

#ifndef BASE64_TABLE_BODY
#define BASE64_TABLE_BODY BASE64_DEFAULT_TABLE_BODY
#endif

static const char encode_table[65] = ;

/**
 * @brief encode 16 bytes into printable string
 *
 * @param input
 * @param encoded
 */
void base64_encode(uint8_t *input, char *encoded) {
  uint8_t j = 0;
  for (uint8_t i = 0; i < ENCODE_SOURCE_SIZE; i += 3) {
    encoded[j + 0] = encode_table[uint8_t(input[i + 0] >> 2)];
    encoded[j + 1] = encode_table[uint8_t((input[i + 0] & 0b00000011) << 4) |
                                  uint8_t(input[i + 1] >> 4)];
    encoded[j + 2] = encode_table[uint8_t((input[i + 1] & 0b11110000) << 4) |
                                  uint8_t(input[i + 2] >> 6)];
    encoded[j + 3] = encode_table[uint8_t(input[i + 2] >> 2)];
    j += 4;
  }
  encoded[ENCODE_SOURCE_SIZE] = 0;
}