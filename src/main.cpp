#include <Arduino.h>
#include "ecu_config.h"

//=============================================================================
//Include ECU abstraction components
#ifdef USE_ED_L298
#include "ed_l298L/ed_l298.h"
#endif

#ifdef USE_CTRL_TRACTION
#include "Ctrl_Traction/ctrl_traction.h"
#endif

#ifdef USE_ED_STEERING_DRIVER
#include "ed_SteeringDriver/ed_steering_driver.h"
#endif

#ifdef USE_CTRL_STEERING
#include "Ctrl_Steering/ctrl_steering.h"
#endif

//==============================================================================

void setup() 
{
//==============================================================================
//Pentru fiecare fir de executie startam fiecare setup()  
  Serial.begin(9600);
  Serial.println("--Initialize Programm--");

  #ifdef USE_ED_L298
    ed_l298_setup();
  #endif  

  #ifdef USE_CTRL_TRACTION
    ctrl_traction_setup();
  #endif

  #ifdef USE_ED_STEERING_DRIVER
    ed_steering_driver_setup();
  #endif  

  #ifdef USE_CTRL_STEERING
    ctrl_steering_setup();
   #endif 

  #if ECU_CONFIG == MASTER
    com_can_send_setup();
  #elif ECU_CONFIG == SLAVE
    com_can_recv_setup(); // presupunând că ai o funcție similară pentru SLAVE
  #endif
}

#define SYS_TICK 1

#define ED_L298_REC (1 / SYS_TICK)
int ed_l298_rec = ED_L298_REC + 1;

#define CTRL_TRCTION_REC (10 / SYS_TICK)
int ctrl_traction_rec = CTRL_TRCTION_REC + 1;

#define ED_STEERING_DRIVER_REC (2 / SYS_TICK)
int ed_steering_driver_rec = ED_STEERING_DRIVER_REC + 1;

#define CTRL_STEERING_REC (10 / SYS_TICK)
int ctrl_steering_rec = CTRL_STEERING_REC + 1;

#define CAN_SEND_REC (500 / SYS_TICK)
int send_rec_cnt = CAN_SEND_REC + 1;

#define CAN_RECV_REC (1 / SYS_TICK)
int recv_rec_cnt = CAN_RECV_REC + 2;


void loop() 
{
#ifdef USE_ED_L298
  if (--ed_l298_rec <= 0)
  {
    ed_l298_loop();
    ed_l298_rec = ED_L298_REC;
  }
#endif

#ifdef USE_CTRL_TRACTION
  if (--ctrl_traction_rec <= 0)
  {
    ctrl_traction_loop();
    ctrl_traction_rec = CTRL_TRCTION_REC;
  } 
#endif

#ifdef USE_ED_STEERING_DRIVER
  if(--ed_steering_driver_rec <= 0)
  {
    ed_steering_driver_loop();
    ed_steering_driver_rec = ED_STEERING_DRIVER_REC;
  }
#endif

#ifdef USE_CTRL_STEERING
  if(--ctrl_steering_rec <= 0)
  {
    ctrl_steering_loop();
    ctrl_steering_rec = CTRL_STEERING_REC;
  }
#endif

#if ECU_CONFIG == MASTER
  if (--send_rec_cnt <= 0)
  { // send data per 100ms
    com_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
    // delay(1000);
  }

#elif ECU_CONFIG == SLAVE
  if (--recv_rec_cnt <= 0)
  {
    com_can_recv_loop();
    recv_rec_cnt = CAN_RECV_REC;
    // delay(1000);
  }
#endif

  delay(SYS_TICK);
}

