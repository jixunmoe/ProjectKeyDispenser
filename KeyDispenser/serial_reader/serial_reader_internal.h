#pragma once
#include <Arduino.h>
#include <stdint.h>

#define SERIAL_READER_BUFFER_SIZE (32)

enum SERIAL_READ_STATE {
  WAIT_NEW_COMMAND = 1,
  READING_COMMAND = 2,
  READING_PARAM = 3,
  RUNNING_COMMAND = 4,
  COMMAND_LOOP_START = 5,
  COMMAND_LOOP = 6,
};

struct serial_reader_ctx;
struct command_pair;

typedef bool (*f_serial_command)(struct serial_reader_ctx *ctx);

typedef struct serial_reader_ctx {
  enum SERIAL_READ_STATE state;
  uint8_t buffer_pointer;

  char buffer[SERIAL_READER_BUFFER_SIZE];

  struct command_pair *commands;
  struct command_pair *running_command;
} serial_reader_ctx;

typedef struct command_pair {
  const char *name;
  f_serial_command callback;
} command_pair;
