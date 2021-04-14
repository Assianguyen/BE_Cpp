#include "LED.h"

Led::Led()
{
    ledOn = false;
}

Led::Led(bool state)
{
    ledOn = state;
    numLed=D3;
}

Led::Led(int num)
{ 
    numLed=num;
    ledOn = false;
}

Led::Led(bool state,int num)
{
    numLed=num;
    ledOn = state;
}


void Led::setLedOn(bool state)
{
    ledOn = state;
}

void Led::setNumLed(int num)
{
    numLed=num;
}
void Led::turnOnLed()
{
    
    digitalWrite(numLed, HIGH);
    
}

void Led::turnOffLed()
{
    
    digitalWrite(numLed, LOW);
    
}

bool Led::isLedOn()
{
    return ledOn;
}

int Led::getNumLed()
{
   return numLed;
}
