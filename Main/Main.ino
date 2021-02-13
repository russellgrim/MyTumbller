#include "Controller.h" 

#include "Pins.h"
#include "PinChangeInt.h"

unsigned char speed = 20;
// volatile unsigned long encoder_count_right_a = 0;
volatile unsigned long encoder_count_left_a = 0;


Controller motor_controler();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA_LEFT, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);
  pinMode(MY_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_A_PIN), encoderCountLeftA, CHANGE);

  // motor_controler.setup();
  carStop();
  carForward(255);
  
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(encoder_count_left_a);
  // motor_controler.loop();
}


void carStop()
{
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(STBY_PIN, HIGH);
  analogWrite(PWMA_LEFT, 0);
}

void carForward(unsigned char speed)
{
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA_LEFT, speed);
}

void encoderCountLeftA()
{
  encoder_count_left_a++;
}