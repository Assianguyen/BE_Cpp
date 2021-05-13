#ifndef ACCELERO_H
#define ACCELERO_H
#include <stdlib.h>
#include <stdint.h>

const int  lengthTab=100;

class Accelero {

  
  protected:

  bool isFalling;
  uint8_t deltaValue;
  uint8_t currentValue;
  uint8_t meanValue;
  uint8_t tabRef[lengthTab]; ///< tableau de valeurs d'accélération référence
  static uint8_t sensorAddress; ///< IIC address of the sensor
  uint8_t tabRef[lengthTab];

  public:

  Accelero();
  Accelero(bool chute, uint8_t valeur,uint8_t*tab,uint8_t moy,uint8_t intervalle);
  //int8_t init(uint8_t range); ///< Initialization function

  int8_t init();
  void setUp(Accelero acc);
  uint8_t getValue(uint8_t address);
  uint8_t writeTab(uint8_t address, uint8_t *regValue, size_t loopnb);
  void readValue(int16_t &z);
  void fillTab (uint8_t address,int loopnb);
  void calculateMean();
  void calculateDelta();
  //void getAcceleration(int16_t&, int16_t&, int16_t&); ///< read x, y, z data
  bool detectFall();
    
};

#endif
