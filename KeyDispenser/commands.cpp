#include "commands.h"
#include "password_derive/base64_encode.h"
#include "password_derive/derive.h"

bool command_help(serial_reader_ctx *ctx) {
  Serial.println("help:");
  Serial.println("  !derive                Derive next password.");
  Serial.println("  !set_secret <16 char>  Set a new secrect.");
  return true;
}

bool command_set_password(serial_reader_ctx *ctx) {
  Serial.println("enter cmd: command_set_password");
  return true;
}

unsigned char password[] = "0123456789ABCDEF";

bool command_derive_key(serial_reader_ctx *ctx) {
  char plain[17];
  base64_encode(password, plain);
  Serial.println(String("current password: ") + plain);
  derive(password);
  base64_encode(password, plain);
  Serial.println(String("    new password: ") + plain);
  memset(plain, 0, sizeof(plain));
  return true;
}

#define MAX_SECRET_SIZE (16)

bool command_set_secret(serial_reader_ctx *ctx) {
  if (ctx->state == SERIAL_READ_STATE::COMMAND_LOOP_START) {
    Serial.println("input 16 chars as your new secret: ");
  }

  auto read_size = Serial.available();
  if (read_size > 0) {
    int remaining_bytes = MAX_SECRET_SIZE - ctx->buffer_pointer;
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

  if (ctx->buffer_pointer >= MAX_SECRET_SIZE) {
    Serial.println("read ok, new secret applied.");
    derive((uint8_t *)ctx->buffer);
    memcpy(password, ctx->buffer, MAX_SECRET_SIZE);
    return true;
  }

  return false;
}
