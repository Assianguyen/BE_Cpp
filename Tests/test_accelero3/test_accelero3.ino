
#include "Accelero.h"
#include <Wire.h>

Accelero LIS=Accelero(); //Accelerometer

void setup(){
  LIS.setUp();
  
}

void loop(){
  acceleration();

}

/*!
 *  @brief Print the position result.
 */
void acceleration(void)
{
  int16_t z;

  delay(100);
  Serial.print("Acceleration z: "); //print acceleration
  Serial.println(LIS.getZ());
  //Serial.println(z);
  LIS.calculateMean();
  Serial.print("Valeur moyenne: "); //print acceleration
  //Serial.println(LIS.calculateMean());
  Serial.println(LIS.getMeanValue());
  
  LIS.calculateDelta();
  Serial.print("Valeur écart: "); //print acceleration
  Serial.println(LIS.getDelta());
  //==Serial.println(LIS.calculateDelta());
  if (LIS.detectFall()){
    Serial.println("Patient has fallen");
    Serial.println("-------------------------------------------------------");
  }
  
  
}
