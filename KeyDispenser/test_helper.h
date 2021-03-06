#pragma once
#include "password_derive/crc32.h"
#include <Arduino.h>

void test_crc32(uint32_t expected, const char *text, int len) {
  Serial.print("Testing crc32[");
  Serial.print(text);
  Serial.print(", ");
  Serial.print(String(len, 10));
  Serial.print("]: 0x");
  auto actual = crc32_proper(text, len);
  Serial.print(String(actual, 16));
  Serial.print(" - ");
  Serial.println((actual == expected)
                     ? String("OK")
                     : String("ERROR, expecting 0x") + String(expected, 16));
}

void run_self_test() {
  Serial.println("[*] Running self test...");
  test_crc32(0x03b4c26d, "hello world!", 12);
  Serial.println("[*] Done!");
  Serial.println("");
}
