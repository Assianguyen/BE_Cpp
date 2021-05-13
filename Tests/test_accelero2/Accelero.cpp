#include "Accelero.h"
#include <Wire.h>
#include <cstdlib>
#include <Arduino.h>


uint8_t Accelero::sensorAddress = 0x18; //  0x18

Accelero::Accelero(){
  isFalling=false;
  currentValue=0;
  tabRef[0]=0;
  meanValue=0;
  deltaValue=0;
  
}

Accelero::Accelero(bool chute, uint8_t valeur,uint8_t*tab,uint8_t moy,uint8_t intervalle){
  
  isFalling=chute;
  currentValue=valeur;
  *tabRef=*tab;
  meanValue=moy;
  deltaValue=intervalle;
}

int8_t Accelero::init()
{
    int8_t ret = 0;
    Wire.beginTransmission(sensorAddress);
    ret = Wire.endTransmission();
    if(ret != 0){
       ret = -1;
    }else{
        uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00, 0x00, 0x00};
        ret = (int8_t)writeTab(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
    }
    return ret;
}

void Accelero::setUp(Accelero acc){
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  while(acc.init() == -1){  //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
}

uint8_t Accelero::getValue(uint8_t address){
    Wire.beginTransmission(sensorAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress,(uint8_t)1);
    currentValue = Wire.read();
    return currentValue;
}

uint8_t Accelero::writeTab(uint8_t address, uint8_t *regValue, size_t loopnb)
{
    for(size_t i = 0; i < loopnb; i++){
        Wire.beginTransmission(sensorAddress);
        Wire.write(address+i);
        Wire.endTransmission();
        Wire.requestFrom(sensorAddress,(uint8_t)1);
        regValue[i] = Wire.read();
    }
}

void Accelero::readValue(int16_t &z) //read z data
{
    fillTab(0xA8, 6);
   // x = ((int8_t)tabRef[1])*256+tabRef[0]; //return values
   // y = ((int8_t)tabRef[3])*256+tabRef[2];
    z = ((int8_t)tabRef[5])*256+tabRef[4];
}

void Accelero::fillTab(uint8_t address,int loopnb){
  address = 0x80 | address;
  for (uint8_t i = 0; i < loopnb; i++){
    Wire.beginTransmission(sensorAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress,(uint8_t)1);
    tabRef[i] = Wire.read();
  }
  
}

void Accelero::calculateMean(){
  meanValue=0;
  uint8_t sum=0;
  for (uint8_t i = 0; i < lengthTab; i++){
    sum+=tabRef[i];
  }
  meanValue=abs(sum/lengthTab);
}

void Accelero::calculateDelta(){
  deltaValue=meanValue+1000; // 
}

bool Accelero::detectFall(){
    if(abs(currentValue-meanValue)>deltaValue){
      isFalling=true;    
    }else{
      isFalling=false;
    }
    return isFalling;
  
}
