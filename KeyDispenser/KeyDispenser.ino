#include "commands.h"
#include "serial_reader/serial_reader.h"
#include <Arduino.h>

#if __has_include("config.local.h")
#include "config.local.h"
#endif

#if RUN_SELF_TEST
#include "test_helper.h"
#endif

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
  Serial.println(" ---- KeyDispenser ---- ");

  init_commands();
  serial_init(&g_sctx, cmds);

#if RUN_SELF_TEST
  Serial.println("[*] Running self test...");
  testCRC32(0x03b4c26d, "hello world!", 12);
  Serial.println("[*] Done!");
  Serial.println("");
#endif

  Serial.println("init ok: hello!");
}

void loop() { serial_process_event(&g_sctx); }
