#pragma once
#include "stdint.h"

class MockEEPROM {
public:
  MockEEPROM &update(int addr, uint8_t byte);
  template <typename T> MockEEPROM &get(int addr, T &result);
};

static MockEEPROM EEPROM;
