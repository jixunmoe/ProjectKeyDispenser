#pragma once

#include "password.h"
#include "password_derive/base64_encode.h"
#include "password_derive/common.h"
#include "pin_monitor/pin_monitor.h"

#include <Arduino.h>
#include <Keyboard.h>

void action_type_password(struct pin_monitor_ctx *ctx) {
  if (ctx->is_active) {
    char plain[ENCODE_DEST_SIZE + 1] = {};
    base64_encode(password, plain);
    Keyboard.print(plain);
    Keyboard.write(KEY_RETURN);
    memset(plain, 0, sizeof(plain));
  }
}
