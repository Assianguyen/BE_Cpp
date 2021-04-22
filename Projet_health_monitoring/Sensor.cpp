#include "Sensor.h"
#include <limits>

Sensor::Sensor()
{
	atRisk = false;
	minValue = numeric_limits<float>::min();
	maxValue = numeric_limits<float>::max();
}

/*Sensor::Sensor(bool state)
{
	atRisk = state;
	minValue = numeric_limits<int>::min();
	maxValue = numeric_limits<int>::max();
}

Sensor::Sensor(int min, int max)
{
	atRisk = false;
	minValue = min;
	maxValue = max;
}
*/
Sensor::Sensor(bool stateRisk, bool stateWarning, float min, float max, int port)
{
	atRisk = stateRisk;
  warning = stateWarning;
	minValue = min;
	maxValue = max;
 numPort = port;
}

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
