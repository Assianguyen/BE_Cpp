#include <Wire.h>
#include <Arduino.h>
#include "Accelerometer.h"

uint8_t Accelerometer::sensorAddress = 0; //  0x18 pour que ça marche
int Accelerometer::nbSample=0;


Accelerometer::Accelerometer(){
  
  atRisk=false;
  sensorAddress=0;
  nbSample=0;
}


Accelerometer::Accelerometer(bool isFalling, uint8_t address, int echantillon){
  
  atRisk=isFalling;
  sensorAddress=address;
  nbSample=echantillon;
}

void Accelerometer::setUp(){
  
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  
  while(init() == -1){  //Equipment connection exception or I2C address error
    //Serial.println("No I2C devices found");
    delay(1000);
  }
   
}

int8_t Accelerometer::init()
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

float Accelerometer::getValue(){
    uint8_t sensorData[6];
    fillTab(0xA8,sensorData,6);
    int16_t zBrut = ((int8_t)sensorData[5])*256+sensorData[4];
    int16_t z=(int32_t)zBrut*1000/(1024*2);
    return z;
}

void Accelerometer::fillTab(uint8_t address, uint8_t *tabvalue,uint8_t tabsize, bool autoIncrement)
{   
    address = 0x80 | address;
    if(autoIncrement){
        Wire.beginTransmission(sensorAddress);
        Wire.write(address);
        Wire.endTransmission();
        Wire.requestFrom(sensorAddress, tabsize);
        for(uint8_t i=0; i < tabsize; i++)
            tabvalue[i] = Wire.read();
    }else{
        for(uint8_t i = 0; i < tabsize; i++){
            Wire.beginTransmission(sensorAddress);
            Wire.write(address+i);
            Wire.endTransmission();
            Wire.requestFrom(sensorAddress,(uint8_t)1);
            tabvalue[i] = Wire.read();
        }
    }
    
}

uint8_t Accelerometer::writeTab(uint8_t address, uint8_t *tabvalue, size_t tabsize, bool autoIncrement)
{   
    Wire.beginTransmission(sensorAddress);
    if(autoIncrement) {
        Wire.write(address);
        Wire.write(tabvalue, tabsize);
    }
    else {
        for(size_t i = 0; i < tabsize; i++){
            Wire.write(address+i);
            Wire.write(tabvalue[i]);
            if( i<(tabsize-1) ){
                Wire.endTransmission(false);
                Wire.beginTransmission(sensorAddress);
            }
        }
    }
    return Wire.endTransmission(true);
}


int16_t Accelerometer::calculateMean(){
  int16_t meanValue;
  int16_t sum=0;
  for (int i = 0; i < nbSample; i++){
    sum=sum+abs(getValue());
  }
  meanValue=sum/nbSample;
  return meanValue;
}

int16_t Accelerometer::calculateDelta(){
 
 int16_t deltaValue=abs(calculateMean());
 return deltaValue;
}


void Accelerometer::isAtRisk(float value){
    value=abs(getValue()); //currentvalue
    if(abs(value-calculateMean())>calculateDelta()){
      atRisk=true;    
    }else{
      atRisk=false;
    }  
}
