#include "Controller.h" 
#include "Wheel.h"

#include "Pins.h"
#include "PinChangeInt.h"



// instantiation
Wheel left_wheel;

int incomingByte = 0;


void setup() {
  // left_wheel.setup();
  left_wheel.setup();
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), encoderCountLeftA, CHANGE);
}

// the loop function runs over and over again forever
void loop() {
  // left_wheel.loop();
  read_serial();
}

void encoderCountLeftA() {
  left_wheel.encoderCountLeftA();
}

void read_serial() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
  }
  if (incomingByte == 97){
    blink_led();
  }
}

void blink_led() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}