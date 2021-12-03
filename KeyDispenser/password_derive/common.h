#pragma once

#ifndef PROGMEM
#include "pgmspace_fake_impl.h"
#endif

// Key is always 16 char random string
#define SRC_SIZE (16)
#define KEY_SIZE (16)

// simple base64 encode with some twists
#define ENCODE_SOURCE_SIZE (12)
// ENCODE_DEST_SIZE = (ENCODE_SOURCE_SIZE / 3 * 4)
#define ENCODE_DEST_SIZE (16)
