#include "Arduino.h"
#include "ed_l298L/ed_l298.h"

uint8_t ed_l298_pin_in1[ED_L298_NR_OF] = ED_L298_PIN_IN1;
uint8_t ed_l298_pin_in2[ED_L298_NR_OF] = ED_L298_PIN_IN2;
uint8_t ed_l298_pin_ena[ED_L298_NR_OF] = ED_L298_PIN_ENA;

ed_l298_t ed_l298_list[ED_L298_NR_OF];

void ed_l298_setup()
{
    for(uint8_t driver_id; driver_id < ED_L298_NR_OF; driver_id++)
    {
        pinMode(ed_l298_pin_in1[driver_id], OUTPUT);
        pinMode(ed_l298_pin_in2[driver_id], OUTPUT);
        pinMode(ed_l298_pin_ena[driver_id], OUTPUT);

        digitalWrite(ed_l298_pin_in1[driver_id], LOW);
        digitalWrite(ed_l298_pin_in2[driver_id], LOW);
        analogWrite(ed_l298_pin_ena[driver_id], LOW);
    }
}


void ed_l298_loop()
{
  
}

void ed_l298_set(uint8_t id_driver,uint8_t in1_state,uint8_t in2_state, uint8_t ena_state)
{
   if ((in1_state == 1) && (in2_state == 0))
   {
     digitalWrite(ed_l298_pin_in1[id_driver], HIGH);
     digitalWrite(ed_l298_pin_in2[id_driver], LOW);
     analogWrite(ed_l298_pin_ena[id_driver], ena_state);
   }
   else if ((in1_state == 0) && (in2_state == 1))
   {
     digitalWrite(ed_l298_pin_in1[id_driver], LOW);
     digitalWrite(ed_l298_pin_in2[id_driver], HIGH);
     analogWrite(ed_l298_pin_ena[id_driver], ena_state);
   }
   else 
   {
     digitalWrite(ed_l298_pin_in1[id_driver], LOW);
     digitalWrite(ed_l298_pin_in2[id_driver], LOW);
     analogWrite(ed_l298_pin_ena[id_driver], 0);
   }
   
}

