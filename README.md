# ProjectKeyDispenser

随机密码生成器与管理方案。

## Dev notes

### Formatting

It should be using `LLVM` format style.

### Setup for VSCode

Install MSYS2 (with clang) and Arduino IDE, then setup
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
