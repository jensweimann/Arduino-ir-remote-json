#include "IRMessage.h"

// Simple constructor
IRMessage::IRMessage() {

}

// Constructor with IRcode
IRMessage::IRMessage(decode_results *results) {
  type = results->decode_type;

  if (type == UNKNOWN) {
    bits = results->rawlen - 1;
    for (int i = 0; i <= bits; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
      } 
      else {
        // Space
        rawCodes[i] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
      }
    }
  }
  else {
    value = results->value;
    bits = results->bits;
  }
}

// Send JsonObject to serial
void IRMessage::send() {

  // Creating Json Object
  JsonObject& root = jsonBuffer.createObject();
  root["type"] = type;
  root["value"] = value;
  root["bits"] = bits;

  for (int i = 0; i<=bits; i++) {
    root["rawCodes"][i] = rawCodes[i];
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
  type = (int) root["type"];
  value = (unsigned long) root["value"];
  bits = (int) root["bits"];

  for ()

  // Send ir signal
  irSend();
}

// Sending ir signal
void IRMessage::irSend() {

  // -1 == UNKNOW
  if (type == UNKNOWN) {
    irsend.sendRaw(rawCodes, bits, 38);
  }
  // 1 == RC5, 2 == RC6
  else if (type == RC5 || type == RC6) {
    // Put the toggle bit into the code to send
    value = value & ~(1 << (bits - 1));
    value = value | (toggle << (bits - 1));
    if (type == RC5) {
      irsend.sendRC5(value, bits);
    } 
    else {
      irsend.sendRC6(value, bits);
    }
  }
  // 3 == NEC
  else if (type == NEC) {
    irsend.sendNEC(value, bits);
  }
  // 4 == SONY
  else if (type == SONY) {
    irsend.sendSony(value, bits);
  }
  // 5 == PANASONIC
  else if (type == PANASONIC) {
    irsend.sendPanasonic(value, bits);
  }
  // 6 == JVC
  else if (type == JVC) {
    // TODO : last param = repeat
    irsend.sendJVC(value, bits, false);
  }
  // 7 == SAMSUNG
  else if (type == SAMSUNG) {
    irsend.sendSAMSUNG(value, bits);
  }
}



