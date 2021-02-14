#include "Led.h"
#include "Pins.h"



Led::Led() {;} // Constructor

Led::~Led() {;} // Destructor

void Led::setup (){
    pinMode(MY_LED, OUTPUT);
}

void Led::loop (){
    if (_is_blinking){
        if ( _is_blink_time() ) {
            toggle_led_state();
            previous_change_time = millis();
        }
    }
}

void Led::start_blinking (){
    _is_blinking = true;
}

void Led::stop_blinking (){
    _is_blinking = false;
    led_state = LOW;
    digitalWrite(MY_LED, led_state);
}

bool Led::_is_blink_time(){
    if ( millis() - previous_change_time > blink_period ){
        return true;
    } else {
        return false;
    }
}

void Led::toggle_led_state(){
    if (led_state == LOW) {
        led_state = HIGH;
    } else {
        led_state = LOW;
    }
    digitalWrite(MY_LED, led_state);
}