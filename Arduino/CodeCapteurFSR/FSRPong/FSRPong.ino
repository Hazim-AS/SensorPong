int fsrAnalogPin = 2; 
int LEDpin = 11;  
int infrarougePin =8;
int fsrReading;  
int nbrTouche = 0;




void interuptFSR(){
  Serial.print("Touche");
  digitalWrite(LEDpin,HIGH); 
  nbrTouche = nbrTouche+1;
  Serial.println(nbrTouche);
    
}


 
void setup(void) {
  Serial.begin(9600);  
  pinMode(LEDpin, OUTPUT);
  
  pinMode(fsrAnalogPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(fsrAnalogPin), interuptFSR, RISING);
}
 
void loop(void) {

  
  fsrReading = analogRead(fsrAnalogPin);
  Serial.println(fsrReading);
  delay(500);

  






//Partie FSR Sans interruption
  /*
  Serial.print("PressionCapteur = ");
  Serial.println(fsrReading);

  if( fsrReading = 0){
    Serial.println("Aucune Touche");
    digitalWrite(LEDpin,LOW);
  }else if(fsrReading > 1){
  Serial.print("Touche");
  digitalWrite(LEDpin,LOW);

  }*/
}


 
