#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
#include "Actuator.h"

class Potentiometer : public Actuator {

friend class Monitoring;
protected :

	int intensity;

public :

	//constructeur

	Potentiometer();

	Potentiometer(int level, int port);

	//fonctions annexes

	void setIntensity(int level);

	int getIntensity();

  virtual void setUp();

};

#endif
