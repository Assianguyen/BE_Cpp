#include "Buzzer.h"

Buzzer::Buzzer()
{
	buzzerOn = false;
}

Buzzer::Buzzer(bool state)
{
	buzzerOn = state;
}

void Buzzer::setBuzzerOn(bool state)
{
	buzzerOn = state;
}

bool Buzzer::isBuzzerOn()
{
	return buzzerOn;
}
