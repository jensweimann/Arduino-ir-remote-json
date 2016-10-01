#include "IRMessage.h"

// Simple constructor
IRMessage::IRMessage() {

}

// Constructor with IRcode
IRMessage::IRMessage(decode_results *results) {
  type = results->decode_type;
  value = results->value;
  bits = results->bits;
}

// Send JsonObject to serial
void IRMessage::send() {

  // Creating Json Object
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = type;
  root["value"] = value;
  root["bits"] = bits;

  // Print json to serial
  root.printTo(Serial);
}

// Decode json (from serial)
void IRMessage::decode(String message) {

  // Convert message to char array
  int str_len = message.length() + 1;
  char char_array[str_len];
  message.toCharArray(char_array, str_len);

  // Parse json
  JsonObject& root = jsonBuffer.parseObject(char_array);

  // Set properties
  type = (int) root["type"];
  value = (unsigned long) root["value"];
  bits = (int) root["bits"];

  // Send ir signal
  irSend();
}

// Sending ir signal
void IRMessage::irSend() {
  // If NEC
  if (type == NEC) {
    irsend.sendNEC(value, bits);
  }
  // If SAMSUNG
  else if (type == SAMSUNG) {
    irsend.sendSAMSUNG(value, bits);
  }
}


