#include "IRMessage.h"

Message::Message() {
  
}

Message::Message(decode_type_t decode_type, unsigned long value, int rawlen) {
  decode_type = decode_type;
  value = value;
  rawlen = rawlen;
}

Message::Message(decode_type_t decode_type, unsigned long value, int rawlen, unsigned int address) {
  decode_type = decode_type;
  value = value;
  rawlen = rawlen;
  address = address;
}

Message::Message(decode_results *results) {
  decode_type = results->decode_type;
  value = results->value;
  Serial.println(results->value);
  rawlen = results->bits;
  Serial.println(results->bits);
  address = results->address;
}

void Message::send() {
  JsonObject& root = jsonBuffer.createObject();
  root["decode_type"] = (int) decode_type;
  root["value"] = value;
  root["rawlen"] = rawlen;
    
  if (decode_type == PANASONIC) {
    root["address"] = address;
  }

  root.printTo(Serial);
}

void Message::decode(String message) {

  // Convert message to char array
  int str_len = message.length() + 1;
  char char_array[str_len];
  message.toCharArray(char_array, str_len);

  // Parse json
  JsonObject& root = jsonBuffer.parseObject(char_array);

  decode_type = (decode_type_t)(int) root["decode_type"];
  value = (unsigned long) root["value"];
  rawlen = (int) root["rawlen"];
  address = (unsigned int) root["address"];

  irSend();
}

void Message::irSend() {
  // If NEC
  if (decode_type == NEC) {
    irsend.sendNEC(value, rawlen);
  }
  else if (decode_type == SAMSUNG) {
    irsend.sendSAMSUNG(value, rawlen);
  }  
}


