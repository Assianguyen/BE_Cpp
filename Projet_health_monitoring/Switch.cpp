#include "Switch.h"

//constructeur vide
Switch::Switch(){
	isOn = false;
}

//constructeur avec attributs
Switch::Switch(bool state, int port){
	isOn = state;
  numPort = port;
}

//setter
void Switch::setSwitchOn(bool state){
	isOn = state;
}

//getters
bool Switch::isSwitchOn(){
	return isOn;
}

bool Switch::getValue(){
  int switchValue = digitalRead(numPort);
  bool isHigh = false;
  
  if (switchValue == HIGH){
    isHigh = true;
  }else{
    isHigh = false;
  } 

  return isHigh;
}

//set up du switch
void Switch::setUp(){
  pinMode(numPort,INPUT);
}
