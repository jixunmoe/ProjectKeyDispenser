# ProjectKeyDispenser

随机密码生成器与管理方案。

## Setup for VSCode

Install MSYS2 (with clang) and Arduino IDE, then setup `.vscode/c_cpp_properties.json`:

Note: replace `C:\\path\\to\\Arduino` to the actual path, e.g.:
`C:\\Program Files (x86)\\Arduino`

```json
{
  "configurations": [
    {
      "name": "Arduino/Win",
      "defines": ["USBCON"],
      "includePath": [
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\cores\\arduino\\",
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\variants\\leonardo",

        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\libraries\\EEPROM\\",
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\libraries\\HID\\",
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\libraries\\SPI\\",
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\libraries\\SoftwareSerial\\",
        "C:\\path\\to\\Arduino\\hardware\\arduino\\avr\\libraries\\Wire\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\avr\\include\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\avr\\include\\avr\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\avr\\include\\compat\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\avr\\include\\util\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\lib\\gcc\\avr\\7.3.0\\include\\",
        "C:\\path\\to\\Arduino\\hardware\\tools\\avr\\lib\\gcc\\avr\\7.3.0\\include-fixed\\"
      ],
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "clang-x64",
      "compilerPath": "C:\\msys64\\ucrt64\\bin\\clang++.exe"
    }
  ],
  "version": 4
}
```
