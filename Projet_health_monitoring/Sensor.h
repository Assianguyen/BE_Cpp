#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
using namespace std;

class Sensor {

protected:

    bool atRisk;
    bool warning;
    float maxValue;
    float minValue;
    int numPort;

public:

    //constructeurs
    Sensor();

    Sensor(bool stateRisk, bool stateWarning, float min, float max, int port);

    //fonctions annexes 

    void setAtRisk(bool state);
    void setWarning(bool state);

    float getMinValue();
    float getMaxValue();
    bool getAtRisk();
    bool getWarning();

    virtual void setUp() = 0;
    virtual float getValue()=0;
    virtual void isAtRisk(float value) = 0;
    //destructeur

};

#endif
