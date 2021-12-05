#include "pin_monitor.h"

#include <Arduino.h>
#include <Keyboard.h>

#define TOGGLE_THRESHOLD (50)

void pin_monitor_init(struct pin_monitor_ctx *ctx, uint8_t pin,
                      f_pin_state_change onchange) {
  pinMode(pin, INPUT_PULLUP);

  memset(ctx, 0, sizeof(struct pin_monitor_ctx));
  ctx->pin = pin;
  ctx->is_active = false;
  ctx->last_toggle = 0;
  ctx->onchange = onchange;
}

void pin_process_event(struct pin_monitor_ctx *ctx) {
  unsigned long now = millis();

  // simple debounce
  if (now - ctx->last_toggle < TOGGLE_THRESHOLD) {
    return;
  }

  bool active = digitalRead(ctx->pin) == LOW;
  if (ctx->is_active != active) {
    ctx->last_toggle = now;
    ctx->is_active = active;
    ctx->onchange(ctx);
  }
}
