#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include <math.h>
#include "Sensor.h"

class Temperature : public Sensor{

  friend class Monitoring;
  
  protected:

    //température d'alerte
    float warningTemp;

  public:

    //constructeurs
    Temperature();
    Temperature(bool stateRisk, bool stateWarning, float min, float warnTemp, float max, int port);

    //méthodes
    virtual void setUp();
    virtual float getValue(); 
    virtual void isAtRisk(float value);
};

#endif
