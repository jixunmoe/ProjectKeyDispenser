#pragma once
#include "serial_reader/serial_reader.h"
#include <Arduino.h>

bool command_help(serial_reader_ctx *ctx);
bool command_set_password(serial_reader_ctx *ctx);
bool command_derive_key(serial_reader_ctx *ctx);
bool command_set_secret(serial_reader_ctx *ctx);
