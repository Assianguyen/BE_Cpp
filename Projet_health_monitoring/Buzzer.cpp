#include "Buzzer.h"

Buzzer::Buzzer()
{
    buzzerOn = false;
}

Buzzer::Buzzer(bool state)
{
    buzzerOn = state;
    numBuzzer=D7;
}

Buzzer::Buzzer(int num)
{ 
    numBuzzer=num;
    buzzerOn = false;
}

Buzzer::Buzzer(bool state,int num)
{
    numBuzzer=num;
    buzzerOn = state;
}


void Buzzer::setBuzzerOn(bool state)
{
    buzzerOn = state;
}

void Buzzer::setNumBuzzer(int num)
{
    numBuzzer=num;
}
void Buzzer::turnOnBuzzer()
{
    
    digitalWrite(numBuzzer, HIGH);
    
}

void Buzzer::turnOffBuzzer()
{
    
    digitalWrite(numBuzzer, LOW);
    
}

bool Buzzer::isBuzzerOn()
{
    return buzzerOn;
}

int Buzzer::getNumBuzzer()
{
   return numBuzzer;
}
