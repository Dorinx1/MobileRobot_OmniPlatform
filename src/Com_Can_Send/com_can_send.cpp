#include "com_can_send.h"   // Include header-ul pentru a lega implementările cu declarațiile

MCP_CAN CAN0_SEND(10);  // Set CS la pin 10

byte MessageBuff_F_DC[8] =  {150,1,150,1,150,1,150,1};
byte MessageBuff_L_SRV[8] = {1,130,1,130,1,130,1,130};/*Servo command*/
byte MessageBuff_B_DC[8] =  {150,0,150,0,150,0,150,0};
byte MessageBuff_R_SRV[8] = {0,130,0,130,0,130,0,130};/*Servo command*/
byte MessageBuff_Center_SRV[8] = {1,1,1,1,1,1,1,1};
byte MessageBuff_S_DC_SRV[8] = {0,0,0,0,0,0,0,0};

char cmd;

// Funcția MSG definită extern pentru a popula matricea

void com_can_send_setup() {
    // Inițializează MCP2515 rulând la 16MHz cu o viteză de 500kb/s și masca și filtrele dezactivate.
    if (CAN0_SEND.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
        Serial.println("MCP2515 inițializat cu succes!");
    } else {
        Serial.println("Eroare la inițializarea MCP2515...");
    }
  
    CAN0_SEND.setMode(MCP_NORMAL);  // Schimbă în modul normal pentru a permite trimiterea mesajelor
}

void com_can_send_loop() {
    if (Serial.available() > 0) {
        cmd = Serial.read();
        byte* selectedMessage_Traction = nullptr;
        byte* selectedMessage_Steering = nullptr;

        switch(cmd) {
            case 'w': selectedMessage_Traction = MessageBuff_F_DC; break;
            case 's': selectedMessage_Traction = MessageBuff_S_DC_SRV; break;
            case 'x': selectedMessage_Traction = MessageBuff_B_DC; break;
            case 'r': selectedMessage_Steering = MessageBuff_Center_SRV; break;
            case 'a': selectedMessage_Steering = MessageBuff_L_SRV; break;
            case 'd': selectedMessage_Steering = MessageBuff_R_SRV; break;
            default:
                Serial.println("--Comandă necunoscută--");
                return;
        }

        bool success = false;

        if (selectedMessage_Traction != nullptr) {  // Verifică dacă avem un mesaj de tracțiune
            if (CAN0_SEND.sendMsgBuf(MESSAGE_TRACTION_ID, 0, 8, selectedMessage_Traction) == CAN_OK) {
                Serial.print("MSG_ID: ");
                Serial.print(MESSAGE_TRACTION_ID, HEX);
                Serial.print("\t Comanda '");
                Serial.print(cmd);
                Serial.println("' -> mesaj trimis cu succes");
                success = true;
            } else {
                Serial.print("Eroare la trimiterea mesajului CAN pentru tracțiune: '");
                Serial.print(cmd);
                Serial.println("'...");
            }
        }

        if (selectedMessage_Steering != nullptr) {  // Verifică dacă avem un mesaj de direcție
            if (CAN0_SEND.sendMsgBuf(MESSAGE_STEERING_ID, 0, 8, selectedMessage_Steering) == CAN_OK) {
                Serial.print("MSG_ID: ");
                Serial.print(MESSAGE_STEERING_ID, HEX);
                Serial.print("\t Comanda '");
                Serial.print(cmd);
                Serial.println("' -> mesaj trimis cu succes");
                success = true;
            } else {
                Serial.print("Eroare la trimiterea mesajului CAN pentru direcție: '");
                Serial.print(cmd);
                Serial.println("'...");
            }
        }

        if (!success) {
            Serial.print("Niciun mesaj CAN nu a fost trimis pentru comanda: '");
            Serial.print(cmd);
            Serial.println("'. Verifică codul!");
        }

        Serial.println();
    }
}
