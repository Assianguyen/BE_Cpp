#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>

class Switch {

friend class Monitoring;

protected:
  int numPort;
  bool isOn;

public:

	//constructeur
	Switch();
	Switch(bool state, int port);

	//méthodes
	void setSwitchOn(bool state);
	bool isSwitchOn();
  
  bool getValue();
  void setUp();
  

};

#endif
