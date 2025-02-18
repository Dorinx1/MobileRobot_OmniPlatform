#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#define MASTER 1
#define SLAVE  2

/*--------Chose configuration--------*/
#define ECU_CONFIG MASTER
// #define ECU_CONFIG SLAVE

#if ECU_CONFIG == MASTER
#include "Com_Can_Send/com_can_send.h"
#elif ECU_CONFIG == SLAVE
#include "Com_Can_Receive/com_can_receive.h"
#endif

#endif