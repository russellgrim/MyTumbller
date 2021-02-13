#include "Controller.h" 
#include "Wheel.h"

#include "Pins.h"
#include "PinChangeInt.h"



// instantiation
Wheel left_wheel;
// Controller c;


void setup() {
  // left_wheel.setup();
  left_wheel.setup();
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), encoderCountLeftA, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
  // left_wheel.loop();
  left_wheel.loop();
}


void encoderCountLeftA() {
  left_wheel.encoderCountLeftA();
}