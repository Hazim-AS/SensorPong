#include <ArduinoJson.h>
//Variable pour le numéro des PIN

int fsrAnalogPin = A1;
int fsrDigitalPin = 2;
int LEDpin1 = 11;
int LEDpin2 = 12;
int infraPin = 34;

//Variable à 0
int fsrDigitalReading = 0;
int fsrAnalogReading = 0;
int nbrBalle = 0;
int nbrTouche = 0;
int CIP = 0;


//Fonction interrupt()

void interuptFSR() {
  fsrDigitalReading = digitalRead(fsrDigitalReading);
  Serial.print("Touche digital a = ");
  Serial.println(fsrDigitalReading);
  digitalWrite(LEDpin2, HIGH);
  nbrTouche = nbrTouche + 1;
  Serial.println(nbrTouche);
}

//Fonction envoieJSON
void envoieJson(int balle, int touche) {
  DynamicJsonDocument jsonEnvoie(1024);
  jsonEnvoie["FSR"] = touche;
  jsonEnvoie["INFRAROUGE"] = balle;
  serializeJson(jsonEnvoie, Serial);
}



void setup(void) {
  Serial.begin(9600);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);
  pinMode(fsrAnalogPin, INPUT);
  pinMode(infraPin, INPUT);
  pinMode(fsrDigitalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fsrDigitalPin), interuptFSR, RISING);



}

void loop(void) {

  fsrAnalogReading = analogRead(fsrAnalogPin);
  //fsrDigitalReading = digitalRead(fsrDigitalPin);
  Serial.print("Analogie FSR = ");
  Serial.println(fsrAnalogReading);
  //Serial.println(fsrDigitalReading);
  delay(500);

  while (nbrBalle != 10) {

    CIP = digitalRead(infraPin);

    Serial.print(" NUMERO FSR = ");
    Serial.println(fsrAnalogReading);
    Serial.print(" NUMERO INFRA = ");
    Serial.println(CIP);

    if (CIP == 1 && fsrAnalogReading >= 1 ) {
      digitalWrite(LEDpin1, HIGH);
      digitalWrite(LEDpin2, HIGH);
      Serial.println("INFRA ACTIVER ET FSR ACTIVER");
      nbrBalle = nbrBalle + 1;
      nbrTouche = nbrTouche + 1;
      delay(1000);

    } else if (CIP == 1 && fsrAnalogReading <= 0) {
      digitalWrite(LEDpin1, HIGH);
      digitalWrite(LEDpin2, LOW);
      Serial.println("FSR DESAC ET INFRA ACTIVER");
      nbrBalle = nbrBalle + 1;
      delay(1000);

    } else if (CIP == 0 && fsrAnalogReading >= 1) {
      digitalWrite(LEDpin1, LOW);
      digitalWrite(LEDpin2, HIGH);
      Serial.println("INFRA DESAC ET FSR ACTIVER");

      delay(1000);

    } else if (CIP == 0 && fsrAnalogReading <= 0) {
      digitalWrite(LEDpin1, LOW);
      digitalWrite(LEDpin2, LOW);
      Serial.println("INFRA DESAC ET FSR DESAC");
      delay(1000);

    }

  }
  Serial.print("Nombre de balle lancer =");
  Serial.println(nbrBalle);
  Serial.print("Nombre de balle toucher =");
  Serial.println(nbrTouche);

  envoieJson(nbrBalle,nbrTouche);

  delay(10000000);


}
