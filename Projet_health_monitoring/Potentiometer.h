#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
#include "Actuator.h"

class Potentiometer : public Actuator {

protected :

	int intensity;

public :

	//constructeur

	Potentiometer();

	Potentiometer(int level);

	//fonctions annexes

	void setIntensity(int level);

	int getIntensity();

};

#endif
