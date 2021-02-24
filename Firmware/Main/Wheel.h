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
    void forward(int speed);
    void carBack(int speed);
    void move (int speed);
    void encoderCountLeftA();
    void encoderCountLeftDecrement();
    void print_current_time_and_encoder();
    void set_mode(String modeIn);

private:
    // unsigned char speed = 20;
    volatile long encoder_count_left_a = 0;
    long previous_position;
    long current_position;
    float speed = 0;
    unsigned long start_time;
    float sample_period = 50.0; //ms
    int previous_sample_time = millis();

    int target_position = 1000; // defult set point
    int position_error_p;
    int position_error_i;

    float Kp_position = 0.003;
    float Ki_position = 0;

    
    //admin
    String mode = "None";
    
    //control
    float target_speed = 0.9; // defult set point
    int pwm;
    float error_p;
    float error_i = 0;
    float Kp = 200;
    float Ki = 0.5;


    bool _is_sample_time();
    void _read_in_sensors();
    void _calculate_speed_pwm_in();
    void _PID_loop();
    void _position_control_pid();
    void _speed_control_pid();
    void _calculate_speed_set_point();
    
};

#endif