#include "Switch.h"

Switch::Switch()
{
	switchOn = false;
}

Switch::Switch(bool state)
{
	switchOn = state;
}

void Switch::setSwitchOn(bool state)
{
	switchOn = state;
}

bool Switch::isSwitchOn()
{
	return switchOn;
}
