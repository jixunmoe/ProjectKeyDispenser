#include "commands.h"
#include "pin_actions.h"
#include "pin_monitor/pin_monitor.h"
#include "serial_reader/serial_reader.h"

#include <Arduino.h>
#include <Keyboard.h>

#if __has_include("config.local.h")
#include "config.local.h"
#else
#define PIN_SEND_PASSWORD (6)
#define RUN_SELF_TEST (0)
#endif

#if RUN_SELF_TEST
#include "test_helper.h"
#endif

static struct pin_monitor_ctx pm_type_password;
static struct serial_reader_ctx g_sctx;

static struct command_pair cmds[] = {
    {.name = "help", .callback = &command_help},
    {.name = "derive", .callback = &command_derive_key},
    {.name = "view_password", .callback = &command_view_password},
    {.name = "set_secret", .callback = &command_set_secret},
    {.name = "auth", .callback = &command_auth},
    {.name = "lock", .callback = &command_lock},
    0};

void setup() {
  Serial.begin(9600);
  delay(50);
  Serial.println(" ---- KeyDispenser ---- ");

  init_commands();
  serial_init(&g_sctx, cmds);

#if RUN_SELF_TEST
  run_self_test();
#endif

  Keyboard.begin();
  pin_monitor_init(&pm_type_password, PIN_SEND_PASSWORD, &action_type_password);

  Serial.println("init ok: hello!");
}

void loop() {
  serial_process_event(&g_sctx);
  pin_process_event(&pm_type_password);
}
