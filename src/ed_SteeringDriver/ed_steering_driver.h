#ifndef _ED_STEERING_DRIVER_H_
#define _ED_STEERING_DRIVER_H_

#include <Servo.h>

#ifndef STEERING_ENB
#define STEERING_ENB {5}
#endif

#ifndef ST_CONT_PIN
#define ST_CONT_PIN {6} 
#endif

void ed_steering_driver_setup();
void ed_steering_driver_loop();
void set_curent_angle();
void set_up_servo_target_angele();
void set_down_servo_target_angele();
uint8_t get_servo_target_angele(uint8_t GetAngle);

#endif