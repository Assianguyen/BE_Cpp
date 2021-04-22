#ifndef HEALTH_MONITORING_H
#define HEALTH_MONITORING_H

#include "Buzzer.h"
#include "Led.h"
#include "Switch.h"
#include "Potentiometer.h"
#include "Temperature.h"
#include "Oxymeter.h"

#include <Arduino.h>

class Monitoring {
	
protected :
  Led led1; //objet LED
  Buzzer buzzer1;
  Switch switch1;
  Potentiometer potent1;
  Temperature temp1;
  Oxymeter oxy1;

public :

  Monitoring();
  Monitoring(Led lum,Buzzer buzz,Switch bouton,Potentiometer pot, Temperature thermo, Oxymeter oxym);

  void setUpMonitoring();

	void startMonitoring();
};

#endif
