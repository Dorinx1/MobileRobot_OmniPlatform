#ifndef _ED_L298L_H_
#define _ED_L298L_H_

#ifndef ED_L298_PIN_IN1
#define ED_L298_PIN_IN1 {2}
#endif

#ifndef ED_L298_PIN_IN2
#define ED_L298_PIN_IN2 {4}
#endif

#ifndef ED_L298_PIN_ENA
#define ED_L298_PIN_ENA {3}
#endif

void ed_l298_setup();
void ed_l298_loop();
void ed_l298_set(uint8_t in1_state,uint8_t in2_state,uint8_t ena_state);


#endif
// #ifndef _ED_L298L_H_
// #define _ED_L298L_H_

// #ifndef ED_L298_PIN_IN1
// #define ED_L298_PIN_IN1 {2}
// #endif

// #ifndef ED_L298_PIN_IN2
// #define ED_L298_PIN_IN2 {4}
// #endif

// #ifndef ED_L298_PIN_ENA
// #define ED_L298_PIN_ENA {3}
// #endif

// #include "stdint.h"

// typedef struct ed_l298{   // ed_l298_t este o structură care conține starea fiecărui driver L298
//     uint8_t in_1;
//     uint8_t in_2;
//     int32_t ena;
// } ed_l298_t;

// enum l298
// {
//     ED_L298_ID_0,
//     ED_L298_NR_OF
// };

// void ed_l298_setup();
// void ed_l298_loop();
// void ed_l298_set(uint8_t id_driver,uint8_t in1_state,uint8_t in2_state,uint8_t ena_state);

// #endif