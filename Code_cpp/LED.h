#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Alarm.h"

using namespace std;

class Led : public Alarm {

protected:

    bool ledOn;

public:

    //constructeurs
    Led();

    Led(bool state);

    //fonctions annexes 

    void setLedOn(bool state);

    bool isLedOn();

    //destructeur

};

#endif
