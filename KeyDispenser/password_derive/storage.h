#pragma once
#include "common.h"
#include <stddef.h>

void save_password(const uint8_t *password, size_t len);
void read_password(uint8_t *password, size_t len);
