#include "Accelero.h"
#include <Wire.h>

uint8_t Accelero::sensorAddress = 0x18; //	0x18
int8_t Accelero::init()
{
    int8_t ret = 0;
    Wire.beginTransmission(sensorAddress);
    ret = Wire.endTransmission();
    if(ret != 0){
       ret = -1;
    }else{
        uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00,0x00, 0x00};
        ret = (int8_t)writeTab(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
    }
    return ret;
}

void Accelero::readXYZ(int16_t &z) //read x, y, z data
{
    uint8_t sensorData[6];
    fillTab(0xA8,6);
    //x = ((int8_t)sensorData[1])*256+sensorData[0]; //return values
    //y = ((int8_t)sensorData[3])*256+sensorData[2];
    z = ((int8_t)sensorData[5])*256+sensorData[4];
}

uint8_t Accelero::readValue(uint8_t address)
{
    uint8_t value;
    Wire.beginTransmission(sensorAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress, (uint8_t)1);
    value = Wire.read();
    return value;
}

void Accelero::fillTab(uint8_t address, uint8_t quanity, bool autoIncrement)
{   
    address = 0x80 | address;
    if(autoIncrement){
        Wire.beginTransmission(sensorAddress);
        Wire.write(address);
        Wire.endTransmission();
        Wire.requestFrom(sensorAddress, quanity);
        for(uint8_t i=0; i < quanity; i++)
            tabRef[i] = Wire.read();
    }else{
        for(uint8_t i = 0; i < quanity; i++){
            Wire.beginTransmission(sensorAddress);
            Wire.write(address+i);
            Wire.endTransmission();
            Wire.requestFrom(sensorAddress,(uint8_t)1);
            tabRef[i] = Wire.read();
        }
    }
    
}

uint8_t Accelero::writeValue(uint8_t address, uint8_t value)
{
    Wire.beginTransmission(sensorAddress);
    Wire.write(address);
    Wire.write(value);
    return Wire.endTransmission(true);
}

uint8_t Accelero::writeTab(uint8_t address, uint8_t *value, size_t quanity, bool autoIncrement)
{   
    Wire.beginTransmission(sensorAddress);
    if(autoIncrement) {
        Wire.write(address);
        Wire.write(value, quanity);
    }
    else {
        for(size_t i = 0; i < quanity; i++){
            Wire.write(address+i);
            Wire.write(value[i]);
            if( i<(quanity-1) ){
                Wire.endTransmission(false);
                Wire.beginTransmission(sensorAddress);
            }
        }
    }
    return Wire.endTransmission(true);
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
