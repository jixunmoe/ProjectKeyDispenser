#pragma once
#include "serial_reader_internal.h"

void serial_init(serial_reader_ctx *ctx, command_pair *cmds);
void serial_reset_buffer(serial_reader_ctx *ctx);
void serial_process_event(serial_reader_ctx *ctx);
bool serial_read_buffer(serial_reader_ctx *ctx, uint8_t target_size);
