#include <IRremote.h>
#include "IRMessage.h"

// PIN of ir receiver (IR emitter must be D3)
int RECV_PIN = 2;

// IR receiver object
IRrecv irrecv(RECV_PIN);

// Result of IR receiver
decode_results results;

// IRMessage
IRMessage m;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (Serial.available() > 0) {
    m = IRMessage();
    m.decode(Serial.readString());
    delay(50);
    irrecv.enableIRIn();
  }
  else if (irrecv.decode(&results)) {
    m = IRMessage(&results);
    m.send();
    irrecv.resume();
  }
}

