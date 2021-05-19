#include "Potentiometer.h"

Potentiometer::Potentiometer()
{
	intensity = 510; //intensit� moyenne (� regler selon les valeurs possibles)
  numPort=A0;
}

Potentiometer::Potentiometer(int level, int port)
{
	intensity = level;
  numPort=port;
}

void Potentiometer::setIntensity(int level)
{
	intensity = level;
}

int Potentiometer::getIntensity()
{
  intensity=analogRead(numPort);
	return intensity;
}

void Potentiometer::setUp()
{
  Serial.begin(115200);
}
