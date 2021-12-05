#pragma once
#include <stdint.h>

typedef void (*f_pin_state_change)(struct pin_monitor_ctx *ctx);

struct pin_monitor_ctx {
  uint8_t pin;
  bool is_active;
  f_pin_state_change onchange;

  unsigned long last_toggle = 0;
};

void pin_monitor_init(struct pin_monitor_ctx *ctx, uint8_t pin,
                      f_pin_state_change onchange);
void pin_process_event(struct pin_monitor_ctx *ctx);
