#ifndef OXYMETER_H
#define OXYMETER_H

#include <Arduino.h>
#include "Sensor.h"

class Oxymeter : public Sensor {

  friend class Monitoring;
  
protected :

  int ageDiz;
  int ageUnit;
  int age;

public :

    //constructeurs
    Oxymeter();
    Oxymeter(bool stateRisk, bool stateWarning, float min, float max, int port, int yo);

    //méthodes
    void setMaxValue();

    int getAge();
    void setAge(int yo);
    int getAgeDiz();
    void setAgeDiz(int yoD);
    int getAgeUnit();
    void setAgeUnit(int yoU);
    void calculateAge();
    
    virtual void setUp();
    virtual float getValue();
    virtual void isAtRisk(float value);
};

#endif
