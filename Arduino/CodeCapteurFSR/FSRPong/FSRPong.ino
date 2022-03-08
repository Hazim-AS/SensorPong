int fsrAnalogPin = A1; // FSR is connected to analog 1
int LEDpin = 11;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
int nbrTouche = 0;
 
void setup(void) {
  Serial.begin(9600);  
  pinMode(LEDpin, OUTPUT);
}
 
void loop(void) {
 
 
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("PressionCapteur = ");
  Serial.println(fsrReading);

  if( fsrReading < 500){
    //Serial.println("Aucune Touche");
    digitalWrite(LEDpin,LOW);
    delay(500);
  }else if(fsrReading > 500){
    Serial.println("Touche");
    nbrTouche = nbrTouche+1;
    Serial.println(nbrTouche);
    digitalWrite(LEDpin,HIGH);

    
    
    
  }
}

  
 
