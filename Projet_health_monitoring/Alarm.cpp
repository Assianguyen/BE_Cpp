#include "Alarm.h"

Alarm::Alarm(){
  isOn = false;
  numPort=0;
}

Alarm::Alarm(bool state,int port){
  isOn = state;  
  numPort=port;
}

void Alarm::setState(bool state){
	isOn = state;
}


 void Alarm::setPort(int port){
  numPort=port;  
 }
 
bool Alarm::getState() {
	return isOn;
}

int Alarm::getPort() {
  return numPort;
}
