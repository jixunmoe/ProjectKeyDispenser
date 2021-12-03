#ifndef PROGMEM
#include <stdint.h>

#define PROGMEM
#define pgm_read_dword_near(a) (uint32_t{0})
#endif