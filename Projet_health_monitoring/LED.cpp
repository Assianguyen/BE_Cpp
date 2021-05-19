#include "LED.h"

//constructeur vide
Led::Led(){
  isOn = false;
  numPort = 0;
}

//constructeur avec attributs
Led::Led(bool state, int port){
  isOn = state;  
  numPort = port; 
}

//allume la LED
void Led::turnOn(){
  digitalWrite(numPort, HIGH);
  isOn = true;
}

//éteint la LED
void Led::turnOff(){
  digitalWrite(numPort, LOW);
  isOn = false;
}

//set up la LED et la fait clignoter une fois
void Led::setUp(){
  pinMode(numPort, OUTPUT);
  turnOn();
  delay(100);
  turnOff();
}
