#ifndef _COM_CAN_RECEIVE_H_
#define _COM_CAN_RECEIVE_H_

#include <mcp_can.h>
#include <SPI.h>
#include "Ctrl_Traction/ctrl_traction.h"
#include "Ctrl_Steering/ctrl_steering.h"
#include "ed_SteeringDriver/ed_steering_driver.h"
#include "ed_l298L/ed_l298.h"

#define USE_ED_L298
#define USE_CTRL_TRACTION
#define USE_ED_STEERING_DRIVER
#define USE_CTRL_STEERING

#define WHEEL_DC_BL 0x00
#define WHEEL_SERVO_BL 0x01 

#define WHEEL_DC_FL 0x10
#define WHEEL_SERVO_FL 0x11

#define WHEEL_DC_FR 0x20 
#define WHEEL_SERVO_FR 0x21

#define WHEEL_DC_BR 0x30
#define WHEEL_SERVO_BR 0x31

#define L298_ID_0  WHEEL_DC_BL
#define SERVO_ID_0 WHEEL_SERVO_BL

#define L298_ID_1  WHEEL_DC_FL
#define SERVO_ID_1 WHEEL_SERVO_FL

#define L298_ID_2  WHEEL_DC_FR
#define SERVO_ID_2 WHEEL_SERVO_FR

#define L298_ID_3  WHEEL_DC_BR
#define SERVO_ID_3 WHEEL_SERVO_BR

/*Select one of configuration for L298_id_driver to control dc motor */

#define CURRENT_L298_ID L298_ID_0
// #define CURRENT_L298_ID L298_ID_1 
// #define CURRENT_L298_ID L298_ID_2 
// #define CURRENT_L298_ID L298_ID_3 

/*Select one of configuration for Servo */
#define CURRENT_SERVO_ID SERVO_ID_0
// #define CURRENT_SERVO_ID SERVO_ID_1
// #define CURRENT_SERVO_ID SERVO_ID_2
// #define CURRENT_SERVO_ID SERVO_ID_3

extern long unsigned int rxId;
extern unsigned char len;
extern unsigned char rxBuf[8];
extern char msgString[128];  // Array to store serial string

#define CAN0_INT 8  // Set INT to pin 2


// Funcții pentru setare și buclă principală
void com_can_recv_setup();
void com_can_recv_loop();

#endif