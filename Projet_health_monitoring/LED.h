#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Alarm.h"
using namespace std;

class Led : public Alarm {

  friend class Monitoring;
  
public:

    //constructeurs
    Led();
    Led(bool state,int port);
    
    //fonctions annexes 

    virtual void turnOn();
    virtual void turnOff();
    virtual void setUp();

    //destructeur

};

#endif
