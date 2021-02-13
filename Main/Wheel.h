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
    void print_current_time_and_encoder();

private:
    // unsigned char speed = 20;
    volatile unsigned long encoder_count_left_a = 0;
    unsigned long previous_position;
    float speed = 0;
    unsigned long start_time;
    float sample_period = 50.0; //ms
    int previous_sample_time = millis();
    
    bool _is_sample_time();
    void _calculate_speed();
};

#endif