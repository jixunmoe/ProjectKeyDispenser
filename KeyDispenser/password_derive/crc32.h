#include <stdint.h>

// default start: 0xFFFFFFFFu
uint32_t crc32(const uint8_t *data, int data_length, uint32_t start);
