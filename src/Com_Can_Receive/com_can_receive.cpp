#include "com_can_receive.h"

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

/* L298 driver variables */
uint8_t Speed;
bool Dir;

/* Servo driver variables */
bool Dir_servo;
uint8_t Power_Servo;

/* Define message IDs */
#define MESSAGE_L298_ID 0x00   // L298 message ID (constant)
#define MESSAGE_SERVO_ID 0x10  // Servo message ID (constant)

MCP_CAN CAN0_RECV(10);  // Set CS to pin 10

void com_can_recv_setup() {
    if (CAN0_RECV.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        Serial.println("MCP2515 Initialized Successfully!");
    } else {
        Serial.println("Error Initializing MCP2515...");
    }

    CAN0_RECV.setMode(MCP_NORMAL);  // Set operation mode to normal
    pinMode(CAN0_INT, INPUT);  // Configuring pin for /INT input
    Serial.println("MCP slave mode on.........");
}

void com_can_recv_loop() {
    if (!digitalRead(CAN0_INT)) {
        CAN0_RECV.readMsgBuf(&rxId, &len, rxBuf);

        Serial.print("\nMESSAGE_ID: 0x");
        Serial.print(rxId, HEX);

        /* -------------------- Traction Processing -------------------- */
        if (rxId == MESSAGE_L298_ID) {
            switch (CURRENT_L298_ID) {
                case L298_ID_0:
                    Speed = rxBuf[0];
                    Dir = rxBuf[1];
                    break;
                case L298_ID_1:
                    Speed = rxBuf[2];
                    Dir = rxBuf[3];
                    break;
                case L298_ID_2:
                    Speed = rxBuf[4];
                    Dir = rxBuf[5];
                    break;
                case L298_ID_3:
                    Speed = rxBuf[6];
                    Dir = rxBuf[7];
                    break;
                default:
                    Serial.println("Error: Invalid L298_ID");
                    return;
            }
            Serial.print(" | Speed: ");
            Serial.print(Speed);
            Serial.print(" | Dir: ");
            Serial.println(Dir);
            ctrl_traction_move(Speed, Dir);
        }

        /* -------------------- Steering Processing -------------------- */
        else if (rxId == MESSAGE_SERVO_ID) {
            switch (CURRENT_SERVO_ID) {
                case SERVO_ID_0:
                    Dir_servo = rxBuf[0];
                    Power_Servo = rxBuf[1];
                    break;
                case SERVO_ID_1:
                    Dir_servo = rxBuf[2];
                    Power_Servo = rxBuf[3];
                    break;
                case SERVO_ID_2:
                    Dir_servo = rxBuf[4];
                    Power_Servo = rxBuf[5];
                    break;
                case SERVO_ID_3:
                    Dir_servo = rxBuf[6];
                    Power_Servo = rxBuf[7];
                    break;
                default:
                    Serial.println("Error: Invalid SERVO_ID");
                    return;
            }
            Serial.print(" | Dir_Servo: ");
            Serial.print(Dir_servo);
            Serial.print(" | Power_Servo: ");
            Serial.println(Power_Servo);
            ctrl_steering_set_Angle(Dir_servo, Power_Servo);
        } 
        
        /* Unknown Message */
        else {
            Serial.println(" | Unknown CAN message received!");
        }

        /* Print Received Data */
        Serial.print("\t RX_Message: ");
        for (byte i = 0; i < len; i++) {
            sprintf(msgString, " 0x%.2X", rxBuf[i]);
            Serial.print(msgString);
        }
        Serial.println();
    }
}
