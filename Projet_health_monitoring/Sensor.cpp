#include "Sensor.h"
#include <limits>

Sensor::Sensor()
{
	atRisk = false;
	minValue = numeric_limits<int>::min();
	maxValue = numeric_limits<int>::max();
}

Sensor::Sensor(bool state)
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

Sensor::Sensor(bool state, int min, int max)
{
	atRisk = state;
	minValue = min;
	maxValue = max;
}

void Sensor::setAtRisk(bool state)
{
	atRisk = state;
}

void Sensor::setMinValue(int min)
{
	minValue = min;
}

void Sensor::setMaxValue(int max)
{
	maxValue = max;
}

bool Sensor::isAtRisk()
{
	return atRisk;
}

int Sensor::getMinValue()
{
	return minValue;
}

int Sensor::getMaxValue()
{
	return maxValue;
}
