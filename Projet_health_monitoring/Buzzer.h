#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "Alarm.h"

using namespace std;

class Buzzer : public Alarm {

  friend class Monitoring;

protected:

    bool buzzerOn;
    int numBuzzer;

public:

    //constructeurs
    Buzzer();
    Buzzer(bool state);
    Buzzer(int num);
    Buzzer(bool state,int num);

    //fonctions annexes 

    void setBuzzerOn(bool state);
    void setNumBuzzer(int num);
    void turnOnBuzzer();
    void turnOffBuzzer();

    bool isBuzzerOn();
    int getNumBuzzer();
};

#endif
