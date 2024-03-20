// Problème occasionnel sur l'extême rouge il y a des blocages 
// voir pourquoi ...

#include <Servo.h>
#include <SPI.h>
#include <mcp2515.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

struct can_frame canMsg;  //data recu
struct can_frame canMsg1;
struct can_frame canMsg2;

MCP2515 mcp2515(10);

int pos = 0;    // Position du servo


void setup() {

  myservo.attach(3);  // attaches the servo on pin 9 to the servo object

  // Position initiale du servo
  myservo.write(180);
  delay(1500);
  myservo.write(pos);
  // CAN

  // Initialisation des trames

  // Trame 1 = LED VERT -> POSITION EXTREME 0
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0x00; // information utile pour le controle du moteur
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  // Trame 2 = LED ROUGE -> POSITION EXTREME 180
  canMsg2.can_id  = 0x0F6;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0xAA; 
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xAA; // information utile pour le controle du moteur
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  while (!Serial);
  Serial.begin(112500);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("CAN BUS - Test communication global");
}

void loop() {
    // Réception des trames
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
        // Si la trame reçue est la trame 1
        if (canMsg.data[0] == 0x00) {
            // Si la position est extrême = 0, on bloque le bouton vert
             if (pos < 1){
                // on envoie la trame 1 de blocage
                mcp2515.sendMessage(&canMsg1);
                Serial.println("Bouton vert bloqué");
             }
             // Sinon, on modifie la position du servo
             else {
                pos = pos - 1;
                myservo.write(pos);
                Serial.println(">> - 1");
             }
        }
        // Si la trame reçue est la trame 2
        else if (canMsg.data[0] == 0xAA) {
            // Si la position est extrême = 180, on bloque le bouton rouge
             if (pos > 179){
                // on envoie la trame 2 de blocage
                mcp2515.sendMessage(&canMsg2);
                Serial.println("Bouton rouge bloqué");
             }
             // Sinon, on modifie la position du servo
             else {
                pos = pos + 1;
                myservo.write(pos);
                Serial.println(">> + 1");
             }
        }

    }
}
