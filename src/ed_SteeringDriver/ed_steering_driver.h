#ifndef _ED_STEERING_DRIVER_H_
#define _ED_STEERING_DRIVER_H_

#include <Servo.h>
#include <stdint.h>

#define STEERING_ENB 5
#define ST_CONT_PIN 6

void ed_steering_driver_setup();
void ed_steering_driver_loop();
uint8_t set_curent_angle();
uint8_t set_left_servo_target_angele(uint8_t servo_power,uint8_t delta);
uint8_t set_right_servo_target_angele(uint8_t servo_power,uint8_t delta);
void stop_servo();

#endif