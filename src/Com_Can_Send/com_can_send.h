#ifndef _COM_CAN_SEND_H_
#define _COM_CAN_SEND_H_

#include <mcp_can.h>
#include <SPI.h>

#define USE_CAN_MESSAGE

#define MESSAGE_TRACTION_ID  0x00 
#define MESSAGE_STEERING_ID  0x10 

// Declarații pentru funcțiile care vor fi implementate în fișierul .c
void com_can_send_setup();
void com_can_send_loop();

#endif
