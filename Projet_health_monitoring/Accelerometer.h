#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <Wire.h>
#include "Sensor.h"

class Accelerometer : public Sensor{

  friend class Monitoring;

  protected:

    //adresse à laquelle on lit la data
    static uint8_t sensorAddress;  
    
    // nombre d'échantillons nécessaires à la moyenne
    int nbSample;                  
    
  public:

    //constructeurs
    Accelerometer();
    Accelerometer(bool isFalling, uint8_t address, int echantillon);

    //méthodes
    virtual void setUp();
    uint8_t writeTab(uint8_t, uint8_t *, size_t, bool autoIncrement = true);
    int8_t init();
    void fillTab(uint8_t, uint8_t *, uint8_t,bool autoIncrement = true); 
    virtual float getValue();  
    int16_t calculateMean(); 
    int16_t calculateDelta(); 
    virtual void isAtRisk(float value); 
};

#endif
