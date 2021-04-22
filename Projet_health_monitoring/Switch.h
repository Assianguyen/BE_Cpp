#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>
#include "Actuator.h"

class Switch : public Actuator {

friend class Monitoring;

protected:

  bool isOn;

public:

	//constructeur

	Switch();

	Switch(bool state, int port);

	//fonctions annexes

	void setSwitchOn(bool state);
	bool isSwitchOn();
  //pour touch sensor

  bool getValue();

  virtual void setUp();
  

};

#endif
