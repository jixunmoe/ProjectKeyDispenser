#pragma once

#include <stdint.h>
#include <string.h>

#define ADMIN_PASSWORD_LEN (16)

#if __has_include("password_config.local.h")
#include "password_config.local.h"
#else
// as a reference, default password is "hi.keydispenser!"
#define ADMIN_PWD_SALT "$somewhat.secret"
#define ADMIN_PWD_SALT_SIZE strlen(ADMIN_PWD_SALT)
#define ADMIN_PASSWORD_ITER (1024)
#define ADMIN_CRC32_HASH (0xec4b90cd)
#endif

uint32_t hash_admin_password(const char *password, const char *salt,
                             size_t salt_size, uint32_t iter);

inline uint32_t hash_admin_password_use_config(const char *password) {
  return hash_admin_password(password, ADMIN_PWD_SALT,
                             size_t{ADMIN_PWD_SALT_SIZE},
                             uint32_t{ADMIN_PASSWORD_ITER});
}
