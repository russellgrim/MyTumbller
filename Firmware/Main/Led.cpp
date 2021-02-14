#include "Led.h"
#include "Pins.h"

Led::Led() {;} // Constructor

Led::~Led() {;} // Destructor

void Led::setup (){
    pinMode(MY_LED, OUTPUT);
}

void Led::loop (){
    ;
}

void Led::blink (){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000); 
}