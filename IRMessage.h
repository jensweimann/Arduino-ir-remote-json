#ifndef Message_h
#define Message_h

#include <IRremote.h>
#include <ArduinoJson.h>

class Message
{
  public:
    // Type of decode    
    decode_type_t decode_type;
    
    // Value of the signal
    unsigned long value;

    // Rawlen
    int rawlen;

    // Adress, only for Panasonic & Sharp
    unsigned int address;

    // JsonBuffer to create and parse Json
    StaticJsonBuffer<200> jsonBuffer;

    // Object to send IR
    IRsend irsend;
    
    // Simple constructor
    Message();

    // Constructor without address
    Message(decode_type_t decode_type, unsigned long value, int rawlen);

    // Constructor with address
    Message(decode_type_t decode_type, unsigned long value, int rawlen, unsigned int address);

    // Constructor with decode_results
    Message(decode_results *results);

    // Send signal to Serial
    void send();

    // Decode signal and send IR
    void decode(String message);

  private:
    // Send IR
    void irSend();
};

#endif
