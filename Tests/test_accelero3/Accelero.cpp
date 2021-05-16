#include "Accelero.h"
#include <Wire.h>

uint8_t Accelero::sensorAddress = 0x18; //	0x18
int16_t Accelero::meanValue = 0;
int16_t Accelero::deltaValue = 0;

Accelero::Accelero(){
  meanValue=0;
  isFalling=false;
  deltaValue=0;
}
int8_t Accelero::init()
{
    int8_t ret = 0;
    Wire.beginTransmission(sensorAddress);
    ret = Wire.endTransmission();
    if(ret != 0){
       ret = -1;
    }else{
        uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00,0x30,0x00, 0x00};
        ret = (int8_t)writeTab(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
    }
    return ret;
}

void Accelero::readZ(int16_t &z) //read x, y, z data
{
    uint8_t sensorData[6];
    fillTab(0xA8,sensorData,6);
    z = ((int8_t)sensorData[5])*256+sensorData[4];
}

int16_t Accelero::getZ(){
    uint8_t sensorData[6];
    fillTab(0xA8,sensorData,6);
    int16_t z1 = ((int8_t)sensorData[5])*256+sensorData[4];
    int16_t z=(int32_t)z1*1000/(1024*2);
    return z;
}
void Accelero::mgScale(int16_t &z)
{
    z = (int32_t)z*1000/(1024*2); //for 8g scale axis*1000/(1024*4)
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




void Accelero::fillTab(uint8_t address, uint8_t *value,uint8_t quanity, bool autoIncrement)
{   
    address = 0x80 | address;
    if(autoIncrement){
        Wire.beginTransmission(sensorAddress);
        Wire.write(address);
        Wire.endTransmission();
        Wire.requestFrom(sensorAddress, quanity);
        for(uint8_t i=0; i < quanity; i++)
            value[i] = Wire.read();
    }else{
        for(uint8_t i = 0; i < quanity; i++){
            Wire.beginTransmission(sensorAddress);
            Wire.write(address+i);
            Wire.endTransmission();
            Wire.requestFrom(sensorAddress,(uint8_t)1);
            value[i] = Wire.read();
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
/*

void Accelero::calculateMean(){
  int16_t sum=0;
  for (int i = 0; i < 50; i++){
    sum=sum+getZ();
  }
  meanValue=abs(sum/50);
}

*/
/*

void Accelero::calculateMean(int16_t& z){
  int16_t sum=0;
  for (int i = 0; i < 50; i++){
    sum=sum+z;
    //sum+=z;
  }
  //meanValue=abs(sum/50);
  meanValue=abs(sum/50);
}
*/



int16_t Accelero::calculateMean(){
  int16_t meanValue;
  int16_t sum=0;
  for (int i = 0; i < 50; i++){
    sum=sum+abs(getZ());
  }
  meanValue=sum/50;
  return meanValue;
}


int16_t Accelero::getMeanValue(){
  return meanValue;
}

int16_t Accelero::getDelta(){
  return deltaValue;
}


int16_t Accelero::calculateDelta(){
  //deltaValue=meanValue+0.50*meanValue; // arbitraire
  deltaValue=abs(calculateMean());
 return deltaValue;
}


/*
void Accelero::calculateDelta(){
  deltaValue=meanValue; // arbitraire
}
*/

bool Accelero::detectFall(){
    uint8_t currentValue=abs(getZ());
    if(abs(currentValue-calculateMean())>calculateDelta()){
      isFalling=true;    
    }else{
      isFalling=false;
    }
    return isFalling;
  
}

/*
bool Accelero::detectFall(){
    uint8_t currentValue=abs(getZ());
    calculateMean();
    calculateDelta();
    if(abs(currentValue-meanValue)>deltaValue){
      isFalling=true;    
    }else{
      isFalling=false;
    }
    return isFalling;
  
}*/
