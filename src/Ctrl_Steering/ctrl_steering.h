#ifndef _CTRL_STEERING_H_
#define _CTRL_STEERING_H_
 
#include "ed_SteeringDriver/ed_steering_driver.h"

void ctrl_steering_setup();
void ctrl_steering_loop();
void ctrl_steering_set_Angle(const bool angle,const uint8_t power);

#endif