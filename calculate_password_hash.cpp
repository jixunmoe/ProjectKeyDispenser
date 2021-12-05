#include <stdio.h>
#include <stdlib.h>

// use mocks
#define VSCODE_COMPAT

#include "KeyDispenser/password_derive/admin_password.cpp"
#include "KeyDispenser/password_derive/crc32.cpp"

int main()
{
  char password[18] = {};
  char salt[1024] = {};
  uint32_t iter = 1024;

  do
  {
    fprintf(stderr, "// enter password (%d char): ", ADMIN_PASSWORD_LEN);
    if (scanf("%17s", password) != 1) return 1;
  } while (strlen(password) != ADMIN_PASSWORD_LEN);

  do
  {
    fprintf(stderr, "// enter salt (at least 8 char): ");
    if (scanf("%1023s", salt) != 1) return 1;
  } while (strlen(salt) < 8);

  do
  {
    fprintf(stderr, "// enter iter count (recommand: 1024; min: 128): ");
    if (scanf("%u", &iter) != 1) return 1;
  } while (iter < 128);

  auto hash = hash_admin_password(password, salt, strlen(salt), iter);

  printf("// save output to: %s\n",
         "KeyDispenser/password_derive/password_config.local.h");
  printf("// password is: %s\n", password);

  printf("#define ADMIN_PWD_SALT R\"_(%s)_\"\n", salt);
  printf("#define ADMIN_PWD_SALT_SIZE (%ld)\n", strlen(salt));
  printf("#define ADMIN_PASSWORD_ITER (%u)\n", iter);
  printf("#define ADMIN_CRC32_HASH (0x%x)\n", hash);

  return 0;
}
