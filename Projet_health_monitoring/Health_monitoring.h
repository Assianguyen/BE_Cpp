#ifndef HEALTH_MONITORING_H
#define HEALTH_MONITORING_H

#include "LED.h"

#include <Arduino.h>

class Monitoring {
	
protected :

  //a remplacer par alarm
  Led led1; //objet LED

public :

  Monitoring();
  Monitoring(Led lum);

  void setUpMonitoring();

	void startMonitoring();
};

#endif
