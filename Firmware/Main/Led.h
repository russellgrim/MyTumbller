#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led {
public:
    Led ();
    ~Led ();
    void setup();
    void loop();
    void blink();

private:

};

#endif