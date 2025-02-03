#include "Arduino.h"
#include "Ctrl_Steering/ctrl_steering.h"

void ctrl_steering_setup()
{

}

void ctrl_steering_loop()
{

}

void ctrl_steering_set_Angle(const bool angle,const uint8_t power)
{
    if(angle == 1) 
    {
        set_up_servo_target_angele();
    }
    else if(angle == 0)
    {
      set_down_servo_target_angele();  
    }
}
