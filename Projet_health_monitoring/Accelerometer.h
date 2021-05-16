#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include "Sensor.h"

class Accelerometer : public Sensor {

  friend class Monitoring;

  protected:

   
    static uint8_t sensorAddress;  //adresse à laquelle on lit la data
    static int nbSample;                  // nombre d'échantillons nécessaires à la moyenne
    

  public:

    //constructeurs
    Accelerometer();
    Accelerometer(bool isFalling, uint8_t address, int echantillon);
    
    virtual void setUp();
    int8_t init();    //Fonction d'initialisation
    virtual float getValue();   //Retourne l'accélération en z
    void fillTab(uint8_t, uint8_t *, uint8_t,bool autoIncrement = true); // remplit un tableau avec les accélérations
    uint8_t writeTab(uint8_t, uint8_t *, size_t, bool autoIncrement = true); //écrit un tableau d'accélération
    int16_t calculateMean(); //Retourne la valeur moyenne d'accélération en z sur 50 échantillons
    int16_t calculateDelta(); // Retourne la valeur d'écart minimum pour la détection de chute
    virtual void isAtRisk(float value); // Fonction de détection de chute
    

};

#endif
