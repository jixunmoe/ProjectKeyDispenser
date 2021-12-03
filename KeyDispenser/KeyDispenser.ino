#include "commands.h"
#include "serial_reader/serial_reader.h"
#include <Arduino.h>

static struct serial_reader_ctx g_sctx;
static struct command_pair cmds[] = {
    {.name = "help", .callback = &command_help},
    {.name = "derive", .callback = &command_derive_key},
    {.name = "set_secret", .callback = &command_set_secret},
    0};

void setup() {
  Serial.begin(9600);
  serial_init(&g_sctx, cmds);
  Serial.println("init ok: hello!");
}

void loop() { serial_process_event(&g_sctx); }
