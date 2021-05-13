#include "Display.h"

Display::Display()
{
	displayOn = false;
}

Display::Display(bool state)
{
	displayOn = state;
}

void Display::setDisplayOn(bool state)
{
	displayOn = state;
}

bool Display::isDisplayOn()
{
	return displayOn;
}
