#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Alarm.h"
using namespace std;

class Led : public Alarm {

  friend class Monitoring;

protected:

    bool ledOn;
    int numLed;

public:

    //constructeurs
    Led();
    Led(bool state);
    Led(int num);
    Led(bool state,int num);

    //fonctions annexes 

    void setLedOn(bool state);
    void setNumLed(int num);
    void turnOnLed();
    void turnOffLed();

    bool isLedOn();
    int getNumLed();

    //destructeur

};

#endif
