#include "Health_monitoring.h"



Monitoring::Monitoring(){
    led1=Led(false,D3);
    buzzer1=Buzzer(false,D7);
    switch1=Switch(false,D1);
    potent1=Potentiometer(510,A0);
    temp1=Temperature(false, false, 36.0,38.0,40.0,A0);
    oxy1=Oxymeter(false,false,55.0, 200.0,A0,0.0);
}

Monitoring::Monitoring(Led lum,Buzzer buzz, Switch bouton,Potentiometer pot, Temperature thermo,Oxymeter oxym){

    led1=lum;
    buzzer1=buzz;
    switch1=bouton;
    potent1=pot;
    temp1=thermo;
    oxy1=oxym;
}

void Monitoring::setUpMonitoring(){

  led1.setUp(); 
  buzzer1.setUp();
  switch1.setUp();
  potent1.setUp();
  temp1.setUp();
  oxy1.setUp();
  oxy1.setMaxValue();
}

void Monitoring::startMonitoring()
{ 
  //à changer: on print simplement la valeur retournée par le potentiomètre
  //Serial.print("sensor = ");
  //Serial.println(potent1.getIntensity());


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
  /*
  temp1.isAtRisk(temp1.getValue());
  
  if(temp1.getWarning() || temp1.getAtRisk()){
    led1.turnOn();
    buzzer1.turnOn();
    if(temp1.getAtRisk()){
      Serial.println("APPEL URGENCES EN COURS...");
    }
  }*/
  
  delay(500);
  
}
