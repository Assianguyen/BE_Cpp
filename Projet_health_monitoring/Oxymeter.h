#ifndef OXYMETER_H
#define OXYMETER_H

#include <Arduino.h>
#include "Sensor.h"

class Oxymeter : public Sensor {

  friend class Monitoring;
  
protected :

  float age;

public :

    //constructeurs
    Oxymeter();

    Oxymeter(bool stateRisk, bool stateWarning, float min, float max, int port, float yo);

    void setMaxValue();

    float getAge();
    void setAge(float yo);
    
    virtual void setUp();
    virtual float getValue();
    virtual void isAtRisk(float value);
};

#endif
