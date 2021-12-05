#pragma once

// simple base64 encode with some twists
#define ENCODE_SOURCE_SIZE (12)
// ENCODE_DEST_SIZE = (ENCODE_SOURCE_SIZE / 3 * 4)
#define ENCODE_DEST_SIZE (16)

// The EEPROM address to store data. Default: 0
#ifndef EEPROM_PASSWORD_ADDRESS
#define EEPROM_PASSWORD_ADDRESS (0)
#endif
