#include <IRremote.h>
#include "IRMessage.h"

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

Message m;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (Serial.available() > 0) {
    m = Message();
    m.decode(Serial.readString());
    delay(50);
    irrecv.enableIRIn();
  }
  else if (irrecv.decode(&results)) {
    m = Message(&results);
    m.send();
    irrecv.resume();
  }
}

