#include "LED.h"

//constructeurs
Led::Led(){
  isOn = false;
  numPort=0;
}

Led::Led(bool state,int port){
  isOn = state;  
  numPort=port; 
}

//méthodes
void Led::turnOn()
{
  digitalWrite(numPort, HIGH);
  isOn=true;
}

void Led::turnOff()
{
  digitalWrite(numPort, LOW);
  isOn=false;
}

void Led::setUp()
{
  pinMode(numPort,OUTPUT);
  turnOff();
  turnOn();
  delay(100);
  turnOff();
}
