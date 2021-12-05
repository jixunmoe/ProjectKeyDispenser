# ProjectKeyDispenser

随机密码生成器与管理方案。

A somewhat single random password manager.

## Build & Deploy

1. Install Arduino IDE
2. Open the sketch `KeyDispenser`
3. Select menu "Tools" -> "Board" and select "Arduino Leonardo"
4. Select menu "Sketch" -> "Verify/Compile" to check for warnings
5. Connect your "Arduino Pro Micro"
6. Select menu "Tools" -> "Port" and select your device.
7. Select menu "Sketch" -> "Upload"

## Usage

### Admin password setup

With a working g++ compiler, compile and run `calculate_password_hash`:

```sh
g++ -o calculate_password_hash.exe calculate_password_hash.cpp
./calculate_password_hash.exe
```

Answer a few questions:

```cpp
// enter password (16 char): secure_password!
// enter salt (at least 8 char): *q3ajiWUBm*T%4uw
// enter iter count (recommand: 1024; min: 128): 1024
// please save the following to: KeyDispenser/password_derive/password_config.local.h
// password is: secure_password!
#define ADMIN_PWD_SALT R"_(*q3ajiWUBm*T%4uw)_"
#define ADMIN_PWD_SALT_SIZE (16)
#define ADMIN_PASSWORD_ITER (1024)
#define ADMIN_CRC32_HASH (0x866f1848)
```

Save the output above to `KeyDispenser/password_derive/password_config.local.h`.

### Local compile config

Save & update the following content to `config.local.h` before compile.

```cpp
#pragma once

// The pin to be used as "type my password" pin.
// It will be like:
//   pin6 -- switch -- GND
#define PIN_SEND_PASSWORD (6)

// Should it run some simple self test before startup?
//   0 - don't bother
//   1 - run it
#define RUN_SELF_TEST (0)
```

### Commands

Commands are implemented via serial at 9600 baud.

Commands have a prefix of `!`. To view built-in help, type `!help`.

```text
help:
  !auth <16 char>        Authenticate for admin commands

authenticate to view admin commands...
```

Or, when authenticated:

```text
password ok!
help:
  !auth <16 char>        Authenticate for admin commands

admin commands:
  !derive                Derive next password.
  !set_secret <16 char>  Set a new secrect.
  !view_password         View current password.
  !lock                  Remove auth state.
```

#### `auth`

Authenticate your self so you can perform admin actions.

Admin password is determined at compile time.

See [Admin password setup](#admin-password-setup) for information.

##### Syntax

```text
!auth <admin password>
```

Example output:

```text
!auth
enter admin password: 0123456789ABCDEF
password ok!
```

#### `derive`

Derive a new password.

Use this command to generate and save a new password.

##### Syntax

```text
!derive
```

Example output:

```
... secret has been set!
```

#### `view_password`

View current password.

Use this command to preview the password that is going to be typed when
activated.

##### Syntax

```text
!view_password
```

Example output:

```text
Current password: //D///D///D/
```

## Security

This device is weak to defend against physical attacks (e.g. eeprom dump).

I've tried what I could during development. However if you have better ideas
please raise an issue at GitHub.

## Dev notes

### Formatting

It should be using `LLVM` format style.

### Setup for VSCode

Install Arduino IDE v1, then setup
`.vscode/c_cpp_properties.json` with the following content:

```json
{
  "configurations": [
    {
      "name": "Arduino/Win",
      "defines": ["USBCON"],
      "includePath": [
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/",
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/variants/leonardo",

        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/EEPROM/",
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/HID/",
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SPI/",
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/SoftwareSerial/",
        "C:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries/Wire/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/avr/include/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/avr/include/avr/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/avr/include/compat/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/avr/include/util/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/lib/gcc/avr/7.3.0/include/",
        "C:/Program Files (x86)/Arduino/hardware/tools/avr/lib/gcc/avr/7.3.0/include-fixed/"
      ],
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "windows-gcc-x86",
      "compilerPath": "C:/Program Files (x86)/Arduino/hardware/tools/avr/bin/avr-g++.exe"
    }
  ],
  "version": 4
}
```

Note: replace `C:/Program Files (x86)/Arduino` if you installed to a non-default
location.
