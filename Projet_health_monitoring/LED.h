#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "Alarm.h"

class Led : public Alarm {

  friend class Monitoring;
  
  public:

    //constructeurs
    Led();
    Led(bool state, int port);
    
    //méthodes
    virtual void turnOn();
    virtual void turnOff();
    virtual void setUp();
};

#endif
