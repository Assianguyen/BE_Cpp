#include "Accelero.h"
#include <Wire.h>

Accelero LIS; //Accelerometer

void setup(){
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);
  
  while(LIS.init() == -1){  //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
}

void loop(){
  acceleration();
  /*LIS.calculateMean();
  LIS.calculateDelta();
  if (LIS.detectFall()){
    Serial.println("Patient has fallen");
  }*/
}

/*!
 *  @brief Print the position result.
 */
void acceleration(void)
{
  int16_t z;

  delay(100);
  LIS.readXYZ(z);
  Serial.print("Acceleration z: "); //print acceleration
  Serial.println(z);
}
