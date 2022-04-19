const int pinMoteurA = 12;
const int pinMoteurB = 13;

const int speedMoteurA = 3;
const int speedMoteurB = 11;

const int freinMoteurA = 9;
const int freinMoteurB = 8;


void setup() {
  digitalWrite(pinMoteurA, OUTPUT);
  digitalWrite(speedMoteurA,OUTPUT);
  digitalWrite(freinMoteurA,OUTPUT);

  digitalWrite(pinMoteurA,LOW);  
  analogWrite(speedMoteurA,0);
  digitalWrite(freinMoteurA,HIGH);
  
  digitalWrite(pinMoteurB, OUTPUT);
  digitalWrite(speedMoteurB,OUTPUT);
  digitalWrite(freinMoteurB,OUTPUT);

  digitalWrite(pinMoteurB,LOW);  
  analogWrite(speedMoteurB,0);
  digitalWrite(freinMoteurB,HIGH);

  Serial.begin(9600);
  Serial.println( "Demmarage"); 
    
}

void loop() {
  
}


void initialisationPartie(){

  for(int i=0;i<10;i++){
    
  Serial.println(i);
  digitalWrite(pinMoteurB,HIGH);
  analogWrite(speedMoteurB,255);
  digitalWrite(freinMoteurB,LOW);
  Serial.println("Monter Balle pendant 2.5s");
  delay(2500);

  digitalWrite(pinMoteurB,LOW);
  analogWrite(speedMoteurB,0);
  digitalWrite(freinMoteurB,HIGH);
  Serial.println("Fin Monter");
  delay(1000); 
  }
  }

void tirerBalle(int speed){
  int speedBack;
  digitalWrite(pinMoteurA,HIGH); 
  analogWrite(speedMoteurA,speed);
  digitalWrite(freinMoteurA,LOW);
  delay(5000);
  digitalWrite(pinMoteurA,LOW); 
  analogWrite(speedMoteurA,0);
  digitalWrite(freinMoteurA,HIGH);
  return speedBack;
  }

void stopTout(){
  digitalWrite(pinMoteurA,LOW); 
  analogWrite(speedMoteurA,0);
  digitalWrite(freinMoteurA,HIGH);
  
  digitalWrite(pinMoteurB,LOW); 
  analogWrite(speedMoteurB,0);
  digitalWrite(freinMoteurB,HIGH);
  
  }
