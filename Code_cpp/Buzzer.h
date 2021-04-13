#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "Alarm.h"

using namespace std;

class Buzzer : public Alarm {

protected:

    bool buzzerOn;

public:

    //constructeurs
    Buzzer();

    Buzzer(bool state);

    //fonctions annexes 

    void setBuzzerOn(bool state);

    bool isBuzzerOn();

    //destructeur

};

#endif
