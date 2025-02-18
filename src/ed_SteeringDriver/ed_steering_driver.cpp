#include "Arduino.h"
#include "ed_SteeringDriver/ed_steering_driver.h"

typedef struct Angle_DG{           
    uint8_t Angle_0;
    uint8_t Angle_90;
    uint8_t Angle_180;
}Angle;
  
Servo myServo;
uint8_t Current_Steering_Angle;
Angle P1 = {0,90,180}; 

void ed_steering_driver_setup()
{
    pinMode(STEERING_ENB,OUTPUT);
    myServo.attach(ST_CONT_PIN);
    set_curent_angle();
}

void ed_steering_driver_loop()
{

}

uint8_t set_curent_angle()
{
    analogWrite(STEERING_ENB,130);
    myServo.write(P1.Angle_90);
    Current_Steering_Angle = P1.Angle_90;
    delay(100);
    return Current_Steering_Angle;
}

uint8_t set_left_servo_target_angele(uint8_t servo_power,uint8_t delta)
{
    if(Current_Steering_Angle > P1.Angle_0 && Current_Steering_Angle < P1.Angle_180)
    {
        int Set_Target_Angle = Current_Steering_Angle - delta;
        analogWrite(STEERING_ENB, servo_power);
        myServo.write(Set_Target_Angle);
        Current_Steering_Angle = Set_Target_Angle;
        delay(100);
    }
    else
    {
        Serial.println(" ed_steering_driver -> L.fault ");
    }
    return Current_Steering_Angle;
}

uint8_t  set_right_servo_target_angele(uint8_t servo_power,uint8_t delta)
{
    if(Current_Steering_Angle > P1.Angle_0 && Current_Steering_Angle <= P1.Angle_180)
    {
        int Set_Target_Angle = Current_Steering_Angle + delta;
        analogWrite(STEERING_ENB, servo_power);
        myServo.write(Set_Target_Angle);
        Current_Steering_Angle = Set_Target_Angle;
        delay(100);
    }
    else
    {
        Serial.println(" ed_steering_driver -> R.fault ");
    }
    return Current_Steering_Angle;
}

void stop_servo()
{
    digitalWrite(STEERING_ENB,LOW);
}
