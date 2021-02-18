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
    void set_mode(String modeIn);

private:
    // unsigned char speed = 20;
    volatile unsigned long encoder_count_left_a = 0;
    unsigned long previous_position;
    unsigned long current_position;
    float speed = 0;
    unsigned long start_time;
    float sample_period = 50.0; //ms
    int previous_sample_time = millis();

    int target_position = 1000;
    unsigned long position_error_p;
    unsigned long position_error_i;

    float Kp_position = 0.01;
    float Ki_position = 0;
    
    //admin
    String mode = "None";
    
    //control
    float target_speed = 0.5;
    unsigned char pwm;
    float error_p;
    float error_i = 0;
    float Kp = 1000;
    float Ki = 300;


    bool _is_sample_time();
    void _calculate_speed();
    void _calculate_speed_pwm_in();
    void _PID_loop();
    void _position_control_pid();
    void _calculate_speed_set_point();
};

#endif