# Arduino-ir-remote-json
Sketch arduino to send and receive IR signal with serial json communication.

This librairy was created to communicate in Json with NodeJs or other languages.
Arduino-ir-remote-json is based on [IRremote] (https://github.com/z3t0/Arduino-IRremote) and [ArduinoJson] (https://github.com/bblanchon/ArduinoJson).

## Hardware

### Boards

Only tested on Arduino Uno.

### IR Sensors

Only tested with Grove Sensors : 
- [IR Emitter] (http://wiki.seeedstudio.com/wiki/Grove_-_Infrared_Emitter)
- [IR Receiver] (http://wiki.seeedstudio.com/wiki/Grove_-_Infrared_Receiver) 

## Installation

- Clone repository
- Install [IRremote] (https://github.com/z3t0/Arduino-IRremote) and [ArduinoJson] (https://github.com/bblanchon/ArduinoJson) with Arduino IDE library manager.
- Build and Upload on Board !

## Configuration

You can configure **IR receiver PIN** and **Serial Port**. Go to Arduino-ir-remote.json and change it. 


    // PIN of ir receiver (IR emitter must be D3)
    const int RECV_PIN = 2;

    // Port for Serial
    const int SERIAL_PORT = 9600;

## JSON

    {"type":3,"value":1270282502,"bits":32}

### Type

| Int   | Device                  | Test |
|-------|-------------------------|------|
| -1    | UNKNOW                  | N    |
| 0     | UNUSED                  | N    |
| 1     | RC5                     | N    |
| 2     | RC6                     | N    |
| 3     | NEC                     | Y    |
| 4     | SONY                    | Y    |
| 5     | PANASONIC               | N    |
| 6     | JVC                     | N    |
| 7     | SAMSUNG                 | Y    |
| 8     | WHYNTER                 | N    |
| 9     | AIWA_RC_T501            | N    |
| 10    | LG                      | N    |
| 11    | SANYO                   | N    |
| 12    | MITSUBISHI              | N    |
| 13    | DISH                    | N    |
| 14    | SHARP                   | N    |
| 15    | DENON                   | N    |
| 16    | PRONTO                  | N    |




