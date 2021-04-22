#include "Switch.h"

Switch::Switch()
{
	isOn = false;
}

Switch::Switch(bool state, int port)
{
	isOn = state;
  numPort=port;
}

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
  if (touchValue == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  } 
}

void Switch::setUp()
{

  //Serial.begin(9600); 
  pinMode(numPort,INPUT);
}
