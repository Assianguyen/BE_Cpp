#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
using namespace std;

class Sensor {

protected:

    bool atRisk;
    int maxValue;
    int minValue;

public:

    //constructeurs
    Sensor();

    Sensor(bool state);

    Sensor(int min, int max);

    Sensor(bool state, int min, int max);

    //fonctions annexes 

    void setAtRisk(bool state);

    void setMinValue(int min);

    void setMaxValue(int max);

    bool isAtRisk();

    int getMinValue();

    int getMaxValue();

    //destructeur

};

#endif
