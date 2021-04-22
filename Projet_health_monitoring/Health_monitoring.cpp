#include "Health_monitoring.h"



Monitoring::Monitoring(){
    led1=Led(false,D3);
    buzzer1=Buzzer(false,D7);
    switch1=Switch(false,D1);
    potent1=Potentiometer(510,A0);
    
}

Monitoring::Monitoring(Led lum,Buzzer buzz, Switch bouton,Potentiometer pot){

    led1=lum;
    buzzer1=buzz;
    switch1=bouton;
    potent1=pot;
    
}

void Monitoring::setUpMonitoring(){

  led1.setUp(); 
  buzzer1.setUp();
  switch1.setUp();
  potent1.setUp();
}

void Monitoring::startMonitoring()
{ 
  //à changer: on print simplement la valeur retournée par le potentiomètre
  Serial.print("sensor = ");
  Serial.println(potent1.getIntensity());
  if (switch1.getValue()){
    if (led1.getState()){
      led1.turnOff();
    }
    else{
      led1.turnOn();
    }
    if (buzzer1.getState()){
      buzzer1.turnOff();
    }
    else{
      buzzer1.turnOn();
    }
  }
  delay(500);
  
}
