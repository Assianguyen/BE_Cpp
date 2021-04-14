#ifndef HEALTH_MONITORING_H
#define HEALTH_MONITORING_H

#include "Buzzer.h"
#include "Led.h"

#include <Arduino.h>

class Monitoring {
	
protected :
  Led led1; //objet LED
  Buzzer buzzer1;

public :

  Monitoring();
  Monitoring(Led lum,Buzzer buzz);

  void setUpMonitoring();

	void startMonitoring();
};

#endif
