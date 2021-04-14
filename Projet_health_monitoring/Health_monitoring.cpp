#include "Health_monitoring.h"



Monitoring::Monitoring(){
    led1=Led(false,D3);
    buzzer1=Buzzer(false,D7);
    //led1.setNumLed(D3);
    
}

Monitoring::Monitoring(Led lum, Buzzer buzz){
    led1=lum;
    buzzer1=buzz;
    
}

void Monitoring::setUpMonitoring(){
  
  pinMode(led1.getNumLed(), OUTPUT); 
  pinMode (buzzer1.getNumBuzzer(), OUTPUT);
  
}

void Monitoring::startMonitoring()
{ 
  led1.turnOnLed();
  buzzer1.turnOnBuzzer();
  delay(1000);
  led1.turnOffLed();
  buzzer1.turnOffBuzzer();
  delay(1000);
  
}
