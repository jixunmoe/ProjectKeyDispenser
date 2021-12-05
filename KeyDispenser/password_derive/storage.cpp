#include "storage.h"

#ifdef VSCODE_COMPAT
#include "mock/EEPROM.h"
#else
#include <EEPROM.h>
#endif

void save_password(const uint8_t *password, size_t len) {
  for (int i = 0; i < len; i++) {
    EEPROM.update(EEPROM_PASSWORD_ADDRESS + i, password[i]);
  }
}

void read_password(uint8_t *password, size_t len) {
  for (int i = 0; i < len; i++) {
    EEPROM.get(EEPROM_PASSWORD_ADDRESS + i, password[i]);
  }
}
