#ifndef OXYMETER_H
#define OXYMETER_H

#include <Arduino.h>
#include "Sensor.h"

class Oxymeter : public Sensor {

  friend class Monitoring;
  
  protected :

    //chiffre des dizaines
    int ageDiz;

    //chiffre des unités
    int ageUnit;

    //âge
    int age;

  public :

    //constructeurs
    Oxymeter();
    Oxymeter(bool stateRisk, bool stateWarning, float min, float max, int port, int yo);

    //méthodes    
    void setAge(int yo);
    void setAgeDiz(int yoD);
    void setAgeUnit(int yoU);
    
    int getAge();
    int getAgeDiz();
    int getAgeUnit();
    
    void calculateAge();
    
    virtual void setUp();
    virtual float getValue();
    virtual void isAtRisk(float value);
};

#endif
