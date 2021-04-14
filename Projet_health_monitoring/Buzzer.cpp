#include "Buzzer.h"

Buzzer::Buzzer(){
  isOn = false;
  numPort=0;
}
Buzzer::Buzzer(bool state,int port){
  isOn = state;  
  numPort=port; 
}

void Buzzer::turnOn()
{
    
    digitalWrite(numPort, HIGH);
    isOn=true;
    
}

void Buzzer::turnOff()
{
    
    digitalWrite(numPort, LOW);
    isOn=false;
}

void Buzzer::setUp()
{
    pinMode(numPort,OUTPUT);
    turnOff();
}
