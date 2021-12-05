#include "serial_reader.h"
#include <Arduino.h>

void serial_init(serial_reader_ctx *ctx, command_pair *cmds) {
  memset(ctx, 0, sizeof(serial_reader_ctx));
  ctx->state = SERIAL_READ_STATE::WAIT_NEW_COMMAND;
  ctx->commands = cmds;
}

void serial_reset_buffer(serial_reader_ctx *ctx) {
  ctx->buffer_pointer = 0;
  memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void serial_process_event(serial_reader_ctx *ctx) {
  while (Serial.available() > 0) {
    char c = Serial.peek();
#ifdef DEBUG_SERIAL
    Serial.print("state: ");
    Serial.println(String(ctx->state, 16));
    Serial.print("char: ");
    Serial.println(String("") + c);
#endif
    switch (ctx->state) {
    case SERIAL_READ_STATE::WAIT_NEW_COMMAND:
      Serial.read();
      if (isspace(c))
        continue;
      if (c == '!') {
        ctx->state = SERIAL_READ_STATE::READING_COMMAND;
      }
      break;

    case SERIAL_READ_STATE::READING_COMMAND:
      if (isspace(c)) {
        ctx->state = SERIAL_READ_STATE::RUNNING_COMMAND;
      } else {
        Serial.read();
        auto ptr = ctx->buffer_pointer;
        ctx->buffer[ptr] = c;
        ctx->buffer_pointer = (ptr + 1) & (SERIAL_READER_BUFFER_SIZE - 1);
        break;
      }

    case SERIAL_READ_STATE::READING_PARAM:
      break;

    case SERIAL_READ_STATE::RUNNING_COMMAND: {
      auto this_command = ctx->commands;
      while (this_command->callback != nullptr) {
#ifdef DEBUG_SERIAL
        Serial.print("this_command->name = ");
        Serial.print(this_command->name);
        Serial.print(", ctx->buffer = ");
        Serial.println(ctx->buffer);
#endif
        if (strcmp(this_command->name, ctx->buffer) == 0) {
          ctx->state = SERIAL_READ_STATE::COMMAND_LOOP_START;
          ctx->running_command = this_command;
          serial_reset_buffer(ctx);
          return;
        }
        this_command++;
      }

      Serial.read();
      Serial.print("unknown command: ");
      Serial.println(ctx->buffer);
      ctx->state = SERIAL_READ_STATE::WAIT_NEW_COMMAND;
      ctx->running_command = nullptr;
      serial_reset_buffer(ctx);
    } break;

    case SERIAL_READ_STATE::COMMAND_LOOP_START:
      // Skip this char (whitespace)
      Serial.read();
    case SERIAL_READ_STATE::COMMAND_LOOP:
      if (ctx->running_command) {
        bool done = ctx->running_command->callback(ctx);
        if (done) {
          ctx->running_command = nullptr;
          ctx->state = SERIAL_READ_STATE::WAIT_NEW_COMMAND;
          serial_reset_buffer(ctx);
        } else {
          ctx->state = SERIAL_READ_STATE::COMMAND_LOOP;
          // exit early, it might be expecting more data to be availalbe
          return;
        }
      }
      break;
    }
  }
}

bool serial_read_buffer(serial_reader_ctx *ctx, uint8_t target_size) {
  auto read_size = Serial.available();
  if (read_size > 0) {
    int remaining_bytes = target_size - ctx->buffer_pointer;
    if (remaining_bytes < 0) {
      Serial.println("input overflow, stop processing.");
      return true;
    }

    if (read_size > remaining_bytes) {
      read_size = remaining_bytes;
    }

    ctx->buffer_pointer +=
        Serial.readBytes(&ctx->buffer[ctx->buffer_pointer], read_size);
  }

  return ctx->buffer_pointer >= target_size;
}
