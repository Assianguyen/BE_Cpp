#include "Health_monitoring.h"



Monitoring::Monitoring(){
    led1=Led(false,D3);
    buzzer1=Buzzer(false,D7);
    
}

Monitoring::Monitoring(Led lum,Buzzer buzz){

    led1=lum;
    buzzer1=buzz;
    
}

void Monitoring::setUpMonitoring(){

  led1.setUp(); 
  buzzer1.setUp();
}

void Monitoring::startMonitoring()
{ 
  led1.turnOn();
  buzzer1.turnOn();
  delay(1000);
  led1.turnOff();
  buzzer1.turnOff();
  delay(1000);
  
}
