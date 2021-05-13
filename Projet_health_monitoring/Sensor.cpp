#include "Sensor.h"
#include <limits.h>

//constructeurs
Sensor::Sensor()
{
	atRisk = false;
	minValue = 0.0;
	maxValue = 0.0;
}

Sensor::Sensor(bool stateRisk, bool stateWarning, float min, float max, int port)
{
	atRisk = stateRisk;
  warning = stateWarning;
	minValue = min;
	maxValue = max;
 numPort = port;
}

//méthodes
void Sensor::setAtRisk(bool state)
{
	atRisk = state;
}

void Sensor::setWarning(bool state)
{
  warning = state;
}

float Sensor::getMinValue()
{
	return minValue;
}

float Sensor::getMaxValue()
{
	return maxValue;
}

bool Sensor::getAtRisk()
{
  return atRisk;
}

bool Sensor::getWarning()
{
  return warning;
}
