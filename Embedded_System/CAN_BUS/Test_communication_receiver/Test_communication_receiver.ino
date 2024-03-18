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
const long interval = 100; // 100ms

void setup() {
  
  while (!Serial);
  Serial.begin(112500);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
}

// BOUCLE DU RECEPTEUR
void loop() {
 
  // RECEPTION DE LA TRAME
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("CAN ID : ");
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" : CAN DLC : "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" : CAN DATA : ");
    
    // TRAITEMENT DE LA TRAME -> AFFICHAGE
    for (int i = 0; i<canMsg.can_dlc; i++)  { 
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println(": END BUS");
  }

}