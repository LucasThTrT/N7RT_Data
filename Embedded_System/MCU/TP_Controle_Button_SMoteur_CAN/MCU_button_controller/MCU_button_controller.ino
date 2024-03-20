#include <SPI.h>
#include <mcp2515.h>

// Déclaration de la structure de la trame CAN
struct can_frame canMsg;  //data recu
struct can_frame canMsg1;
struct can_frame canMsg2;

MCP2515 mcp2515(10);

// Déclaration du controle bouton
// Déclaration PIN VERT
const int buttonPinVert = 2;  // the number of the pushbutton pin
const int ledPinVert = 3;    // the number of the LED pin

// Déclaration PIN ROUGE
const int buttonPinRouge = 4;  // the number of the pushbutton pin
const int ledPinRouge = 5;    // the number of the LED pin

// variables will change:
// VERT
int buttonStateVert = 0;  // variable for reading the pushbutton status
bool buttonLockVert = false; // variable pour bloquer le bouton si position extrême

// ROUGE
int buttonStateRouge = 0;  // variable for reading the pushbutton status
bool buttonLockRouge = false; // variable pour bloquer le bouton si position extrême

void setup() {

  // CAN

  // Initialisation des trames

  // Trame 1 = LED VERT 
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x00; // information utile pour le controle du moteur
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  // Trame 2 = LED ROUGE 
  canMsg2.can_id  = 0x0F6;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0xAA; // information utile pour le controle du moteur
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
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


  // CONTROLE BOUTON

  // SETTING VERT
  // initialize the LED pin as an output:
  pinMode(ledPinVert, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinVert, INPUT);

  // SETTING ROUGE
  // initialize the LED pin as an output:
  pinMode(ledPinRouge, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinRouge, INPUT);

}

void loop() {

// Controle du Servo moteur par le bouton

  // VERT
  // read the state of the pushbutton value:
  buttonStateVert = digitalRead(buttonPinVert);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateVert == HIGH) {
    // turn LED on:
    digitalWrite(ledPinVert, HIGH);
    //Serial.println("HIGH");

    // Position extrême Rouge Impossible
    buttonLockRouge = false;

    // Envoi de la trame CAN
    mcp2515.sendMessage(&canMsg1);
    Serial.println(":: VERT");
  }  else if (buttonLockVert == false) {
    // turn LED off:
    digitalWrite(ledPinVert, LOW);
  }

  // ROUGE
  // read the state of the pushbutton value:
  buttonStateRouge = digitalRead(buttonPinRouge);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateRouge == HIGH ) {
    // turn LED on:
    digitalWrite(ledPinRouge, HIGH);
    //Serial.println("HIGH");

    // Position extrême Vert Impossible
    buttonLockVert = false;

    // Envoi de la trame CAN
    mcp2515.sendMessage(&canMsg2);
    Serial.println(":: ROUGE");

  }  else if (buttonLockRouge == false){
    // turn LED off:
    digitalWrite(ledPinRouge, LOW);
  }

// Si le Servo moteur attend une valeur extreme (0 ou 180), 
// on va allumer la LED correspondante
// Elemination au niveu du controleur du moteur de la fonction tourner à extrem + 1

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    // l'information se trouve en data[3]
    if (canMsg.data[0] == 0x00) {
      digitalWrite(ledPinVert, HIGH);
      buttonLockVert = true;
      Serial.println("Position extrême VERT");

    } else if (canMsg.data[0] == 0xAA) {
      digitalWrite(ledPinRouge, HIGH);
      buttonLockRouge = true;
      Serial.println("Position extrême ROUGE");
    }
  }

  if (buttonLockRouge == true) {
    // Alume la led si bloqué
    digitalWrite(ledPinRouge, HIGH);
  } 
  else if (buttonLockVert == true) {
    // Alume la led si bloqué
    digitalWrite(ledPinVert, HIGH);

  }

}
