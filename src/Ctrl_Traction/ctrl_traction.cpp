#include "Arduino.h"
#include "Ctrl_Traction/ctrl_traction.h"



void ctrl_traction_setup()
{
    
}

void ctrl_traction_loop()
{

}


void ctrl_traction_move(const uint8_t speed, const bool direction)
{
    if (direction == true) 
    {
        ed_l298_set(0x00, 1, 0, speed);
    }
    else 
    {
        ed_l298_set(0x00, 0, 1, speed);
    }
}