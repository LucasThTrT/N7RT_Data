#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;  //data recu
struct can_frame canMsg1;
struct can_frame canMsg2;

MCP2515 mcp2515(10);

// sequencement de l'envoie des trames
int i = 0;

// numéro de la trame
int n = 0;

// fonction pour limiter l'envoie
unsigned long previousMillis = 0;
const long interval = 10;

void setup() {
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = n;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  canMsg2.can_id  = 0x036;
  canMsg2.can_dlc = 5;
  canMsg2.data[0] = 0xAA;
  canMsg2.data[1] = 0xBB;
  canMsg2.data[2] = 0xCC;
  canMsg2.data[3] = 0x08;
  canMsg2.data[4] = 0x01;
  //canMsg2.data[5] = 0x00;
  //canMsg2.data[6] = 0x00;
  //canMsg2.data[7] = 0xA0;
  
  while (!Serial);
  Serial.begin(112500);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  
  unsigned long currentMillis = millis();  

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }   
  }
  if (currentMillis - previousMillis >= interval){
    canMsg1.data[0] = n;
    mcp2515.sendMessage(&canMsg1);
    Serial.print("====>");
    Serial.println(n);
    
    n = n +1;

    previousMillis = currentMillis;
  }
  
// on alterne les 2 trames
//  if (currentMillis - previousMillis >= interval){
//    if (i == 0){
//      mcp2515.sendMessage(&canMsg1);
//      i = i+1;
//      Serial.println("Messages sent1");
//    } else {
//      mcp2515.sendMessage(&canMsg2);
//      i = 0;
//      Serial.println("Messages sent2");
//    }
//  
//    previousMillis = currentMillis;
//  }
}
