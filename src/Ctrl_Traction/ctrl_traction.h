#ifndef _CTRL_TRACTION_H_
#define _CTRL_TRACTION_H_

#include "ed_l298L/ed_l298.h"

void ctrl_traction_setup();
void ctrl_traction_loop();
void ctrl_traction_move(const uint8_t speed, const bool direction);

#endif