#pragma once
#include <stdint.h>

// default start: 0xFFFFFFFF
uint32_t crc32(const void *data, int data_length, uint32_t start);

inline uint32_t crc32_proper(const void *data, int data_length) {
  return crc32(data, data_length, 0xFFFFFFFF);
}
