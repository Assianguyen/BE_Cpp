#include "Potentiometer.h"

Potentiometer::Potentiometer()
{
	intensity = 50; //intensité moyenne (à regler selon les valeurs possibles)
}

Potentiometer::Potentiometer(int level)
{
	intensity = level;
}

void Potentiometer::setIntensity(int level)
{
	intensity = level;
}

int Potentiometer::getIntensity()
{
	return intensity;
}
