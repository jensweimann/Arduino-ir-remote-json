#include <IRremote.h>
#include "IRMessage.h"

// PIN of ir receiver (IR emitter must be D3)
const int RECV_PIN = 2;

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

  // Enable IR receiver
  irrecv.enableIRIn();
}

void loop() {
  // If Json enter
  if (Serial.available() > 0) {
    m = IRMessage();
    m.decode(Serial.readString());
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

