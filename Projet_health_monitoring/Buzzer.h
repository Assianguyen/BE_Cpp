#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "Alarm.h"

using namespace std;

class Buzzer : public Alarm {

  friend class Monitoring;

public:

    //constructeurs
    Buzzer();
    Buzzer(bool state,int port);
    //fonctions annexes 

    virtual void turnOn();
    virtual void turnOff();
    virtual void setUp();
};

#endif
