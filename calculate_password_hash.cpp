#include <iomanip>
#include <iostream>
#include <string>

// use mocks
#define VSCODE_COMPAT

#include "KeyDispenser/password_derive/admin_password.cpp"
#include "KeyDispenser/password_derive/crc32.cpp"

int main() {
  std::string password;
  std::string salt;
  uint32_t iter = 1024;

  do {
    std::cout << "// enter password (" << ADMIN_PASSWORD_LEN << " char): ";
    std::cin >> password;
  } while (password.length() != ADMIN_PASSWORD_LEN);

  do {
    std::cout << "// enter salt (at least 8 char): ";
    std::cin >> salt;
  } while (salt.length() < 8);

  do {
    std::cout << "// enter iter count (recommand: 1024; min: 128): ";
    std::cin >> iter;
  } while (iter < 128);

  auto hash =
      hash_admin_password(password.c_str(), salt.c_str(), salt.length(), iter);

  std::cout << "// save output to: "
               "KeyDispenser/password_derive/password_config.local.h"
            << std::endl;
  std::cout << "// password: " << password << std::endl;

  std::cout << "#define ADMIN_PWD_SALT R\"_(" << salt << ")_\"" << std::endl;
  std::cout << "#define ADMIN_PWD_SALT_SIZE (" << salt.length() << ")"
            << std::endl;
  std::cout << "#define ADMIN_PASSWORD_ITER (" << iter << ")" << std::endl;
  std::cout << "#define ADMIN_CRC32_HASH (" << std::setfill('0') << std::setw(8)
            << hash << ")" << std::endl;

  return 0;
}
