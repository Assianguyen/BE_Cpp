#ifndef HEALTH_MONITORING_H
#define HEALTH_MONITORING_H

#include "LED.h"
#include "Buzzer.h"

#include <Arduino.h>

class Monitoring {
	
protected :

  //a remplacer par alarm
  Led led1; //objet LED
  Buzzer buzzer1; //objet Buzzer

public :

  Monitoring();
  Monitoring(Led lum, Buzzer buzz);

  void setUpMonitoring();

	void startMonitoring();
};

#endif
