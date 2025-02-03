#include "com_can_send.h"   // Include header-ul pentru a lega implementările cu declarațiile


MCP_CAN CAN0_SEND(10);  // Set CS la pin 10

// byte MSG_TX[8][7];  // Redefinim MSG_TX ca un array 8x3 pentru a asigura dimensiunea corectă a mesajului
byte MessageBuff_F_DC[8] =  {200,1,200,1,200,1,200,1};
byte MessageBuff_L_SRV[8] = {1,150,1,150,1,150,1,150};
byte MessageBuff_B_DC[8] =  {200,0,200,0,200,0,200,0};
byte MessageBuff_R_SRV[8] = {0,150,0,150,0,150,0,150};
byte MessageBuff_S_DC_SRV[8] = {0,0,0,0,0,0,0,0};


char cmd;
char msgString_TX[128];

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
        byte* selectedMessage = nullptr;

        switch(cmd) {
            case 'w': selectedMessage = MessageBuff_F_DC; break;
            case 's': selectedMessage = MessageBuff_S_DC_SRV; break;
            case 'x': selectedMessage = MessageBuff_B_DC; break;
            case 'a': selectedMessage = MessageBuff_L_SRV; break;
            case 'd': selectedMessage = MessageBuff_R_SRV; break;
            default:
                Serial.println("--Comandă necunoscută--");
                return;
        }

        if (CAN0_SEND.sendMsgBuf(MESSAGE_ID, 0, 8, selectedMessage) == CAN_OK) {
            Serial.print("ID: ");
            Serial.print(MESSAGE_ID, HEX);
            Serial.print("\t Comanda '");
            Serial.print(cmd);
            Serial.println("' -> mesaj trimis cu succes");
        } else {
            Serial.print("Eroare la trimiterea mesajului CAN pentru comanda '");
            Serial.print(cmd);
            Serial.println("'...");
        }

        Serial.println();
    }
}