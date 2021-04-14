#include "Health_monitoring.h"



Monitoring::Monitoring(){
    led1=Led();
    led1.setNumLed(D3);
}

Monitoring::Monitoring(Led lum){
    led1=lum;
}

void Monitoring::setUpMonitoring(){
  
  pinMode(led1.getNumLed(), OUTPUT); 
  
}

void Monitoring::startMonitoring()
{ 
  led1.turnOnLed();
  delay(1000);
  led1.turnOffLed();
  delay(1000);
}
