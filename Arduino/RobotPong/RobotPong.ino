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

  bool test = false;

  if(test == false){
  faireMonterBalle();
  test = true;
  }

  digitalWrite(12,HIGH); 
  analogWrite(speedMoteurA,255);
  digitalWrite(freinMoteurA,LOW);
}


void faireMonterBalle(){

  for(int i=0;i<10;i++){
    
  Serial.println(i);
  digitalWrite(pinMoteurB,HIGH);
  analogWrite(speedMoteurB,255);
  digitalWrite(freinMoteurB,LOW);
  Serial.println("Monter Balle pendant 5s");
  delay(2500);

  digitalWrite(pinMoteurB,LOW);
  analogWrite(speedMoteurB,0);
  digitalWrite(freinMoteurB,HIGH);
  Serial.println("Fin Monter");
  delay(1000);

  }
  
  
  }

void stopMoteur(char moteur, int frein){

  if(moteur = 'A'){
      digitalWrite(freinMoteurA,frein);
      delay(1000);
  }else if(moteur='B'){
      digitalWrite(freinMoteurB,frein);
      delay(1000); 
  }
}

void bougerMoteur(char moteur, int direction, int speed){

  int pinMoteur;
  int speedMoteur;

  if(moteur == 'A'){
    
  pinMoteur = pinMoteurA;
  speedMoteur = pinMoteurB;
    
  }else if(moteur =='B'){
    
  pinMoteur = pinMoteurB;
  speedMoteur = speedMoteurB;
    
  }


}










/*   digitalWrite(pinMoteurA, OUTPUT);
  digitalWrite(speedMoteurA,OUTPUT);
  digitalWrite(freinMoteurA,OUTPUT);

  Serial.begin(9600);
  Serial.println( "Demmarage");
}

void loop() {

   digitalWrite(pinMoteurA,directionA);
   analogWrite(speedMoteurA,255);
   delay(5000);
   digitalWrite(freinMoteurA,HIGH);
   delay(2000);
   digitalWrite(freinMoteurA,LOW); */




/*

void tirerBalle(){

  digitalWrite(directionMoteurA,HIGH);
  digitalWrite(freinMoteurB,LOW );
  analogWrite(speedMoteurA,255);

  delay(1000);

    digitalWrite(directionMoteurA,LOW);
  digitalWrite(freinMoteurB,HIGH);
  analogWrite(speedMoteurA,255);
  
  }*/
