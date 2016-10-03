#ifndef IRMessage_h
#define IRMessage_h

#include <IRremote.h>
#include <ArduinoJson.h>

class IRMessage
{
  public:
    // Type of decode
    int type;

    // Value of the signal
    unsigned long value;

    // Number of bits
    int bits;

    // RawCodes for unknow devices
    unsigned int rawCodes[RAWBUF];

    // The RC5/6 toggle state
    int toggle = 0;

    // JsonBuffer to create and parse Json
    StaticJsonBuffer<200> jsonBuffer;

    // Object to send IR
    IRsend irsend;
    
    // Simple constructor
    IRMessage();

    // Constructor with decode_results
    IRMessage(decode_results *results);

    // Send signal to Serial
    void send();

    // Decode signal and send IR
    void decode(String message);

  private:
    // Send IR
    void irSend();

    // Send Json Error
    void sendError();
};

#endif
