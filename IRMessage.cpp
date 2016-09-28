#include "IRMessage.h"

// Simple constructor
IRMessage::IRMessage() {
  
}

// Constructor with IRcode
IRMessage::IRMessage(decode_results *results) {
  decode_type = results->decode_type;
  value = results->value;
  rawlen = results->bits;
  address = results->address;
}

// Send JsonObject to serial
void IRMessage::send() {
  JsonObject& root = jsonBuffer.createObject();
  root["decode_type"] = (int) decode_type;
  root["value"] = value;
  root["rawlen"] = rawlen;

  // Only Panasonic have address
  if (decode_type == PANASONIC) {
    root["address"] = address;
  }

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
  decode_type = (decode_type_t)(int) root["decode_type"];
  value = (unsigned long) root["value"];
  rawlen = (int) root["rawlen"];
  address = (unsigned int) root["address"];

  // Send ir signal
  irSend();
}

// Sending ir signal
void IRMessage::irSend() {
  // If NEC
  if (decode_type == NEC) {
    irsend.sendNEC(value, rawlen);
  }
  // If SAMSUNG
  else if (decode_type == SAMSUNG) {
    irsend.sendSAMSUNG(value, rawlen);
  }  
}


