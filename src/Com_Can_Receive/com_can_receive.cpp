#include "com_can_receive.h"

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];  

/*l298 driver var*/
uint8_t Speed;
bool Dir;

/*Servo driver var */
bool Angle;
uint8_t Power;

#define message_l298_id 0x00
#define message_servo_id 0x10

MCP_CAN CAN0_RECV(10);  // Set CS to pin 10


void com_can_recv_setup()
{
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0_RECV.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
    
  CAN0_RECV.setMode(MCP_NORMAL);  // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);  // Configuring pin for /INT input
  
  Serial.println("MCP slave mode on.........");
}


void com_can_recv_loop()
{
  if (!digitalRead(CAN0_INT))  // If CAN0_INT pin is low, read receive buffer
  {
  CAN0_RECV.readMsgBuf(&rxId, &len, rxBuf);  // Read data: len = data length, buf = data byte(s)

    #if CURRENT_L298_ID == 0x00
      if (message_l298_id == rxId)
      {
        Serial.print("\n PCB with ID : ");
        Serial.print(message_l298_id, HEX);
        Serial.print("\t");
        Serial.print(message_servo_id,HEX);
        Speed = rxBuf[0];
        Dir = rxBuf[1];
        ctrl_traction_move(Speed, Dir);
      }
  
    #elif CURRENT_L298_ID  == 0x10
    if(message_l298_id == rxId )
    {
      Serial.print("\n PCB with ID : ");
      Serial.print(message_l298_id, HEX);
      Serial.print("\t");
      Serial.print(message_servo_id,HEX);
      Speed = rxBuf[2];
      Dir = rxBuf[3];
      ctrl_traction_move(Speed, Dir);
    }

    #elif CURRENT_L298_ID == 0x20
    if(message_l298_id == rxId)
    {
      Serial.print("\n PCB with ID : ");
      Serial.print(message_l298_id, HEX);
      Serial.print("\t");
      Serial.print(message_servo_id,HEX);
      Speed = rxBuf[4];
      Dir = rxBuf[5];
      ctrl_traction_move(Speed, Dir);
    }

    #elif CURRENT_L298_ID == 0x30
    if(message_l298_id == rxId)
    {
      Serial.print("\n PCB with ID : ");
      Serial.print(message_l298_id, HEX);
      Serial.print("\t");
      Serial.print(message_servo_id,HEX);
      Speed = rxBuf[6]; 
      Dir = rxBuf[7];
      ctrl_traction_move(Speed, Dir);
    }
    #endif
    
    Serial.print("\t\t RX_Message : ");
    for (byte i = 0; i < len; i++) 
    {
    sprintf(msgString, " 0x%.2X", rxBuf[i]);
    Serial.print(msgString);
    }
  
  }
}

//=========================== versiune a loopului,nu lucreaza bine========




//=======================================Rabociii Variant==============================

// if(ID == ID_0 && ID == rxId)
  // {
  //   Serial.print("\nECU_OMNI_WHEEL_BL L298 with ID_0 : ");
  //   Serial.print(rxId,HEX);
  //   Speed = rxBuf[0];
  //   Dir = rxBuf[1];
  //   ctrl_traction_move(ID,Speed, Dir);
  // }
  // else if(ID == ID_1 && ID == rxId)    
  // {
  //   Serial.print("\nECU_OMNI_WHEEL_FL L298 with ID_1 : ");
  //   Serial.print(rxId,HEX);
  //   Speed = rxBuf[2];
  //   Dir = rxBuf[3];
  //   ctrl_traction_move(Speed, Dir);
  // }
  // else if(ID == ID_2 && ID == rxId)
  // {
  //   Serial.print("\nECU_OMNI_WHEEL_FR L298 with ID_2 : ");
  //   Serial.print(rxId,HEX);
  //   Speed = rxBuf[4];
  //   Dir = rxBuf[5];
  //   ctrl_traction_move(Speed, Dir);
  // }
  // else 
  // {
  //   Serial.print("\nECU_OMNI_WHEEL_BR L298 with ID_3 : ");
  //   Serial.print(rxId,HEX);
  //   Speed = rxBuf[6];
  //   Dir = rxBuf[7];
  //   ctrl_traction_move(Speed, Dir);
  // }

  // Serial.print("\t\t RX_Message : ");
  // for (byte i = 0; i < len; i++) 
  // {
  // sprintf(msgString, " 0x%.2X", rxBuf[i]);
  // Serial.print(msgString);
  // }
  

/*
  if(rxId == ECU_ARM_ID_LIST[])
  {
    Serial.print("ARM with ID : ");
    Serial.print(rxId,HEX);
    Serial.print("\t\t RX_Message : ");

    for (byte i = 0; i < len; i++) 
    {
    sprintf(msgString, " 0x%.2X", rxBuf[i]);
    Serial.print(msgString);
    }

    Serial.println();

      if(ECU_ARM_ID_LIST[i] == 0)
      {
        Speed = digitalRead(rxBuf[0]);
        Dir = digitalRead(rxBuf[1]);
        ctrl_traction_move(Speed, Dir);
      }
      else if(ECU_ARM_ID_LIST[i] == 1)
      {
        Speed = digitalRead(rxBuf[2]);
        Dir = digitalRead(rxBuf[3]);
        ctrl_traction_move(Speed, Dir);
      }
      else if(ECU_ARM_ID_LIST[i] == 2)
      {
        Speed = digitalRead(rxBuf[4]);
        Dir = digitalRead(rxBuf[5]);
        ctrl_traction_move(Speed, Dir);
      }
      else 
      {
        Speed = digitalRead(rxBuf[6]);
        Dir = digitalRead(rxBuf[7]);
        ctrl_traction_move(Speed, Dir);
      }
  }

*/

  /*
    for(uint16_t i = 0; i<ECU_OMNI_WHEEL_ALL;i++)
    {
      if(rxId == ECU_ARM_ID_LIST[i])
      {
        Serial.print("ARM with ID :");
        Serial.println(rxId,HEX);

        for (byte i = 0; i < len; i++) 
        {
          sprintf(msgString, " 0x%.2X", rxBuf[i]);
          Serial.print(msgString);
          
          ctrl_traction_move(rxBuf[0], rxBuf[1]);
        }
        Serial.println("\n Traction Motor is active -> moving forward");
      }
      else if(rxId == ECU_ARM_ID_LIST[i])
      {
        Serial.print("ARM with ID :");
        Serial.println(rxId,HEX);

        for (byte i = 0; i < len; i++) 
        {
          sprintf(msgString, " 0x%.2X", rxBuf[i]);
          Serial.print(msgString);

        }
        Serial.println("\n Traction Motor is active -> moving backward");
      }
      else if(rxId == ECU_ARM_ID_LIST[i])
      {
        Serial.print("ARM with ID :");
        Serial.println(rxId,HEX);

        for (byte i = 0; i < len; i++) 
        {
          sprintf(msgString, " 0x%.2X", rxBuf[i]);
          Serial.print(msgString);
        
        }
        Serial.println("\n Traction Motor is active -> Stop Motor");
      }
    }

    */

//=====================================================================================
    /*if ((rxId & 0x80000000) == 0x80000000)  // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    Serial.print(msgString);
  
    if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else {
      for (byte i = 0; i < len; i++) {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }
    */    