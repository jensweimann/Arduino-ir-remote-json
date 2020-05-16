#include <IRremote.h>
#include "IRMessage.h"

const int RECV_PIN = 2;
const int SEND_PIN = 3;

// Port for Serial
const int SERIAL_PORT = 9600;

// IR receiver object
IRrecv irrecv(RECV_PIN);

// Result of IR receiver
decode_results results;

// IRMessage
IRMessage m;

// Setup
void setup() {
  // Config Serial
  Serial.begin(SERIAL_PORT);
  pinMode(SEND_PIN, OUTPUT);
  // Enable IR receiver
  irrecv.enableIRIn();
  while (!Serial) {
    // wait serial port initialization
  }
  StaticJsonBuffer<50> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["ready"] = "v1";
  root.printTo(Serial);
  Serial.println();
}

void loop() {
  // If Json enter
  if (Serial.available() > 0) {
    m = IRMessage();
    m.decode(Serial.readStringUntil('\n'));
    delay(50);
    irrecv.enableIRIn();
  }
  // If IR signal enter
  else if (irrecv.decode(&results)) {
    m = IRMessage(&results);
    m.send();
    irrecv.resume();
  }
}
