#include "Arduino.h"
#include "Ctrl_Steering/ctrl_steering.h"

void ctrl_steering_setup()
{

}

void ctrl_steering_loop()
{

}


/*delta - este numarul de grade cu care se schimba pozitia servo motorul */
void ctrl_steering_set_Angle(bool direction,const uint8_t power)
{
  if(direction == 0)
  {
    set_right_servo_target_angele(power,5);
  }
  else if(direction == 1)
  {
    set_left_servo_target_angele(power,5);
  }
  else if(direction == 0 && power == 0)
  {
    stop_servo();
  }
  else if(direction == 1 && power == 1)
  {
    set_curent_angle();
  }
  else
  {
    Serial.println("Ctrl_Steering.cpp -> fault");
  }
  
}
