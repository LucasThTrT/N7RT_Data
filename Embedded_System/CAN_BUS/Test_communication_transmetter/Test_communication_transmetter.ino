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
  // CREATION DES BUS

  // BUS 1
  canMsg1.can_id  = 0x0F6; // ID DE LA TRAME
  canMsg1.can_dlc = 8;     // LONGEUR DU MESSAGE
  canMsg1.data[0] = n;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  // BUS 2
  canMsg2.can_id  = 0x036;  // ID DE LA TRAME
  canMsg2.can_dlc = 5;      // LONGUEUR DU MESSAGE
  canMsg2.data[0] = 0xAA;   // DONNE FIXE SUR LE MSSG 2
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

// BOUCLE DE L'EMETTEUR
void loop() {
  
  // INITIALISATION DU TIMER
  unsigned long currentMillis = millis();  

  // EMISSION 
  //on alterne l'envoie des 2 trames grâce a la variable i -> 0 ou 1

  // emission toutes les 100 ms (interval de temps)
  if (currentMillis - previousMillis >= interval){
    if (i == 0){ // ENVOI BUS 1
      mcp2515.sendMessage(&canMsg1);
      i = i+1;
      Serial.println("Messages sent1");
      n = n+1; // on change l'information du bus
    } 
    else { // ENVOI BUS 2
      mcp2515.sendMessage(&canMsg2);
      i = 0;
     Serial.println("Messages sent2");
   }
 
  previousMillis = currentMillis;
  }
}