#include "Switch.h"

//constructeurs
Switch::Switch()
{
	isOn = false;
}

Switch::Switch(bool state, int port)
{
	isOn = state;
  numPort=port;
}

//méthodes
void Switch::setSwitchOn(bool state)
{
	isOn = state;
}

bool Switch::isSwitchOn()
{
	return isOn;
}

bool Switch::getValue()
{
  int touchValue = digitalRead(numPort);
  if (touchValue == HIGH) {
    return true;
  } else {
    return false;
  } 
}

void Switch::setUp()
{
  pinMode(numPort,INPUT);
}
