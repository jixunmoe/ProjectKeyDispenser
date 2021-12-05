#include "admin_password.h"
#include "crc32.h"

#ifndef htole32
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define htole32(value) (uint32_t{value})
#else
#define htole32(value) __builtin_bswap32(value)
#endif
#endif

// Admin password hash calculation (little-endian):
uint32_t hash_admin_password(const char *password, const char *salt,
                             size_t salt_size, uint32_t iter) {
  uint32_t hash = crc32_proper(password, ADMIN_PASSWORD_LEN);
  hash = htole32(crc32(salt, salt_size, hash ^ 0xFFFFFFFF));

  for (uint32_t i = 0; i < iter; i++) {
    hash = crc32_proper(&hash, sizeof(hash));
    hash = htole32(crc32(salt, salt_size, hash ^ 0xFFFFFFFF));
  }

  return hash;
}
