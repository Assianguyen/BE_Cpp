#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>
#include "Actuator.h"

class Switch : public Actuator {

protected:

	bool switchOn;

public:

	//constructeur

	Switch();

	Switch(bool state);

	//fonctions annexes

	void setSwitchOn(bool state);

	bool isSwitchOn();

};

#endif
