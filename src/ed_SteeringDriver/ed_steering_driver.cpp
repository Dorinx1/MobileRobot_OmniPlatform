#include "Arduino.h"
#include "ed_SteeringDriver/ed_steering_driver.h"

Servo myServo;
uint8_t Current_Angle = 90;
uint8_t Max_angle = 180;
uint8_t Setup_Angle = 90;
uint8_t Min_angle = 0;


void ed_steering_driver_setup()
{
    pinMode(STEERING_ENB,OUTPUT);

    myServo.attach(ST_CONT_PIN);

    if(Current_Angle == Setup_Angle) set_curent_angle();
}

void ed_steering_driver_loop()
{

}

void set_curent_angle()
{
    myServo.write(Setup_Angle);
}

void set_up_servo_target_angele()
{
    if(Current_Angle < Max_angle)
    {
    uint8_t set_target_angle = 1;
    Current_Angle += set_target_angle;
    uint8_t get_target_angle = get_servo_target_angele(Current_Angle);
    Current_Angle = get_target_angle;
    myServo.write(Current_Angle);
    }
}    
 
void set_down_servo_target_angele() 
{
    if(Current_Angle > Min_angle)
    {
    uint8_t set_target_angle = 1;
    Current_Angle -= set_target_angle;
    uint8_t get_target_angle = get_servo_target_angele(Current_Angle);
    Current_Angle = get_target_angle;
    myServo.write(Current_Angle);
    }
}    

uint8_t get_servo_target_angele(uint8_t GetAngle) {
    if (GetAngle > Max_angle) return Max_angle;
    if (GetAngle < Min_angle) return Min_angle;
    return GetAngle;
}
