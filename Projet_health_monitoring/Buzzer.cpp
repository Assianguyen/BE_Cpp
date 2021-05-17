#include "Buzzer.h"

//constructeur vide
Buzzer::Buzzer(){
  isOn = false;
  numPort=0;
}

//constructeur avec attributs
Buzzer::Buzzer(bool state,int port){
  isOn = state;  
  numPort=port; 
}

//allume le buzzer
void Buzzer::turnOn(){
  digitalWrite(numPort, HIGH);
  isOn=true; 
}

//éteint le buzzer
void Buzzer::turnOff(){
  digitalWrite(numPort, LOW);
  isOn=false;
}

//set up le buzzer et le fait bipper une fois
void Buzzer::setUp(){
  pinMode(numPort,OUTPUT);
  turnOn();
  delay(100);
  turnOff();
}
