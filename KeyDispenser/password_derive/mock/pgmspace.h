#pragma once

#ifdef VSCODE_COMPAT
#include <stdint.h>

#define PROGMEM
#define pgm_read_dword_near(ptr) (uint32_t{*(const uint32_t *)(ptr)})
#endif
