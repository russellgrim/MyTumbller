#ifndef Wheel_h
#define Wheel_h

#include "Arduino.h"

class Wheel {
public:
    Wheel (); // Constructor
    ~Wheel(); // Destructor
    void setup();
    void loop();
    void stop();
    void forward(unsigned char speed);
    void encoderCountLeftA();

private:
    // unsigned char speed = 20;
    volatile unsigned long encoder_count_left_a = 0;
};

#endif