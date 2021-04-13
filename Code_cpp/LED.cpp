#include "LED.h"

Led::Led()
{
    ledOn = false;
}

Led::Led(bool state)
{
    ledOn = state;
}

void Led::setLedOn(bool state)
{
    ledOn = state;
}

bool Led::isLedOn()
{
    return ledOn;
}
