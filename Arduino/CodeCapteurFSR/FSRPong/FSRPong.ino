//Variable pour le numéro des PIN
int fsrAnalogPin = A1;
int fsrDigitalPin = 2; 
int LEDpin1 = 11;
int LEDpin2 = 12;  
int infraPin = 34;

//Variable à 0
int fsrDigitalReading = 0;
int fsrAnalogReading= 0;
int nbrBalle = 0;
int nbrTouche = 0;
int CIP = 0;


//Fonction interrupt()

void interuptFSR(){
  fsrDigitalReading = digitalRead(fsrDigitalReading);
  Serial.print("Touche digital a = ");
  Serial.println(fsrDigitalReading);
  digitalWrite(LEDpin2,HIGH); 
//  nbrTouche = nbrTouche+1;
//  Serial.println(nbrTouche);   
}


 
void setup(void) {
  Serial.begin(9600);  
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2,OUTPUT);
  pinMode(fsrAnalogPin,INPUT);
  pinMode(infraPin,INPUT);
  pinMode(fsrDigitalPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fsrDigitalPin), interuptFSR, RISING);
}
 
void loop(void) {
 
  fsrAnalogReading = analogRead(fsrAnalogPin);
  //Serial.print("Analogie FSR = ");
  //Serial.println(fsrAnalogReading);


  








 /*

  while(nbrBalle !=10){
    
  CIP = digitalRead(infraPin);
  //fsrReading = analogRead(fsrAnalogPin);
  Serial.print(" NUMERO FSR = ");
  Serial.println(fsrReading);
  Serial.print(" NUMERO INFRA = ");
  Serial.println(CIP);
  
  if(CIP == 1 && fsrReading >= 1  ){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    Serial.println("INFRA ACTIVER ET FSR ACTIVER");
    nbrBalle = nbrBalle+1;
    nbrTouche = nbrTouche+1;
    delay(1000);
    
  }else if(CIP == 1 && fsrReading <= 0){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,LOW);
    Serial.println("FSR DESAC ET INFRA ACTIVER");
    nbrBalle = nbrBalle+1;
    delay(1000);
    
  }else if(CIP == 0 && fsrReading >=1){
    digitalWrite(LEDpin1,LOW);
    digitalWrite(LEDpin2,HIGH);
    Serial.println("INFRA DESAC ET FSR ACTIVER");
    
    delay(1000);
    
  }else if(CIP == 0 && fsrReading <=0){
    digitalWrite(LEDpin1,LOW);
    digitalWrite(LEDpin2,LOW);
    Serial.println("INFRA DESAC ET FSR DESAC");
    delay(1000);
    
  }

  }   
    Serial.print("Nombre de balle lancer =");
    Serial.println(nbrBalle);
    Serial.print("Nombre de balle toucher =");
    Serial.println(nbrTouche);
    delay(10000000);
   
  
  
//InfraRouge TEST
/*
CIP = digitalRead(infraPin);

if(CIP==1){
  digitalWrite(LEDpin1,HIGH);
}else{

  digitalWrite(LEDpin1,LOW);
}
delay(10);
*/

 //Interupt FSR
  /*fsrReading = analogRead(fsrAnalogPin);
  Serial.println(fsrReading);
  delay(500);
*/
  


//Partie FSR Sans interruption
  /*
  Serial.print("PressionCapteur = ");
  Serial.println(fsrReading);

  if( fsrReading = 0){
    Serial.println("Aucune Touche");
    digitalWrite(LEDpin1,LOW);
  }else if(fsrReading > 1){
  Serial.print("Touche");
  digitalWrite(LEDpin1,LOW);

  }*/
  
}


 
