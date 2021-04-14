#include "LED.h"

Led::Led(){
  isOn = false;
  numPort=0;
}

Led::Led(bool state,int port){
  isOn = state;  
  numPort=port; 
}


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
}
