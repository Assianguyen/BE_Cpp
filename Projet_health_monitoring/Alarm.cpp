#include "Alarm.h"

//constructeur vide
Alarm::Alarm(){
  isOn = false;
  numPort=0;
}

//constructeur avec attributs
Alarm::Alarm(bool state, int port){
  isOn = state;  
  numPort=port;
}

//setters
void Alarm::setState(bool state){
	isOn = state;
}

void Alarm::setPort(int port){
  numPort=port;  
}

//getters
bool Alarm::getState(){
	return isOn;
}

int Alarm::getPort(){
  return numPort;
}
