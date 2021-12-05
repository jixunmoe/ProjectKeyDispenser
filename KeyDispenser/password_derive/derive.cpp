#include "derive.h"
#include "common.h"
#include "crc32.h"

#define CRC_START_0 (0xd4ef3085)
#define CRC_START_1 (0x8b44f7af)
#define CRC_START_2 (0x02441453)
#define CRC_START_3 (0xc33707d6)

union derive_masks {
  uint64_t qword[2];
  uint32_t dword[4];
  uint16_t word[8];
  uint8_t byte[16];
};

#define DERIVE_ITER_COUNT (0xFF)

void derive(uint8_t *password) {
  derive_masks masks;
  auto password_ptr = (derive_masks *)(password);
  for (int i = 0; i < DERIVE_ITER_COUNT; i++) {
    masks.dword[0] = crc32(password, PASSWORD_LEN, CRC_START_0);
    masks.dword[1] = crc32(password, PASSWORD_LEN, CRC_START_1);
    masks.dword[2] = crc32(password, PASSWORD_LEN, CRC_START_2);
    masks.dword[3] = crc32(password, PASSWORD_LEN, CRC_START_3);

    password_ptr->qword[0] ^= masks.qword[0];
    password_ptr->qword[1] ^= masks.qword[1];
  }
}
