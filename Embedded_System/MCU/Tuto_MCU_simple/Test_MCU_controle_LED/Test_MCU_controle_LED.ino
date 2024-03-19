
// constants won't change. They're used here to set pin numbers:
// Déclaration PIN VERT
const int buttonPinVert = 2;  // the number of the pushbutton pin
const int ledPinVert = 3;    // the number of the LED pin

// Déclaration PIN ROUGE
const int buttonPinRouge = 4;  // the number of the pushbutton pin
const int ledPinRouge = 5;    // the number of the LED pin

// variables will change:
// VERT
int buttonStateVert = 0;  // variable for reading the pushbutton status

// ROUGE
int buttonStateRouge = 0;  // variable for reading the pushbutton status

void setup() {

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


  // initialize serial communication:
  Serial.begin(9600);

}

void loop() {

  // VERT
  // read the state of the pushbutton value:
  buttonStateVert = digitalRead(buttonPinVert);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateVert == HIGH) {
    // turn LED on:
    digitalWrite(ledPinVert, HIGH);
    Serial.println("HIGH");
  } else {
    // turn LED off:
    digitalWrite(ledPinVert, LOW);
  }

  // ROUGE
  // read the state of the pushbutton value:
  buttonStateRouge = digitalRead(buttonPinRouge);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateRouge == HIGH) {
    // turn LED on:
    digitalWrite(ledPinRouge, HIGH);
    Serial.println("HIGH");
  } else {
    // turn LED off:
    digitalWrite(ledPinRouge, LOW);
  }
}
