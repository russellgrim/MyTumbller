#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led {
public:
    Led ();
    ~Led ();
    void setup();
    void loop();
    void start_blinking();
    void stop_blinking();
    void toggle_led_state();

private:
    int blink_period = 1000;
    int previous_change_time = 0;
    int led_state = LOW;
    bool _is_blinking = false;
    bool _is_blink_time();

};

#endif