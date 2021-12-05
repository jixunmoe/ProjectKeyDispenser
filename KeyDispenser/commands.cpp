#include "commands.h"
#include "password_derive/admin_password.h"
#include "password_derive/base64_encode.h"
#include "password_derive/crc32.h"
#include "password_derive/derive.h"
#include "password_derive/storage.h"

bool authenticated = false;
uint8_t password[PASSWORD_LEN];

#define AUTHENTICATION_CHECK()                                                 \
  if (!authenticated) {                                                        \
    Serial.println("Error: Not authenticated.");                               \
    return true;                                                               \
  }

bool command_help(serial_reader_ctx *ctx) {
  Serial.println("help:");
  Serial.println("  !auth <16 char>        Authenticate for admin commands");
  Serial.println("");
  if (authenticated) {
    Serial.println("admin commands:");
    Serial.println("  !derive                Derive next password.");
    Serial.println("  !set_secret <16 char>  Set a new secrect.");
    Serial.println("  !view_password         View current password.");
    Serial.println("  !lock                  Remove auth state.");
    Serial.println("");
  } else {
    Serial.println("authenticate to view admin commands...");
    Serial.println("");
  }
  return true;
}

void init_commands() { read_password(password); }

bool command_lock(serial_reader_ctx *ctx) {
  authenticated = false;
  Serial.println("... locked!");
  return true;
}

bool command_derive_key(serial_reader_ctx *ctx) {
  AUTHENTICATION_CHECK();

  derive(password);
  save_password(password);
  Serial.println("... secret has been set!");
  return true;
}

bool command_view_password(serial_reader_ctx *ctx) {
  AUTHENTICATION_CHECK();

  char plain[ENCODE_DEST_SIZE + 1] = {};
  base64_encode(password, plain);
  Serial.print("Current password: ");
  Serial.println(plain);
  memset(plain, 0, sizeof(plain));
  return true;
}

bool command_set_secret(serial_reader_ctx *ctx) {
  AUTHENTICATION_CHECK();

  if (ctx->state == SERIAL_READ_STATE::COMMAND_LOOP_START) {
    Serial.print("input ");
    Serial.print(String(PASSWORD_LEN, 10));
    Serial.print(" chars as your new secret: ");
  }

  if (serial_read_buffer(ctx, PASSWORD_LEN)) {
    Serial.println("");
    Serial.println("read ok, new secret applied.");
    derive((uint8_t *)ctx->buffer);
    memcpy(password, ctx->buffer, PASSWORD_LEN);
    save_password(password);
    return true;
  }

  return false;
}

bool command_auth(serial_reader_ctx *ctx) {
  if (ctx->state == SERIAL_READ_STATE::COMMAND_LOOP_START) {
    Serial.print("enter admin password: ");
  }

  if (serial_read_buffer(ctx, ADMIN_PASSWORD_LEN)) {
    Serial.println("");
    auto actual_hash = hash_admin_password_use_config(ctx->buffer);
    authenticated = actual_hash == ADMIN_CRC32_HASH;
    if (authenticated) {
      Serial.println("password ok!");
    } else {
      Serial.println("invalid password!");
    }
    return true;
  }

  return false;
}
