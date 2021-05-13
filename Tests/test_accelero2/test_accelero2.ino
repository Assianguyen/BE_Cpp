#include <Wire.h>
#include "Accelero.h"

Accelero accel=Accelero();

void setup() {
  accel.setUp(accel);

}

void loop() {
  delay(300);
  int16_t z;
  accel.readValue(z);
  Serial.print("Acceleration: ");
  Serial.println(z);
  accel.fillTab (0xA8,lengthTab);
  //accel.calculateMean();
  //accel.calculateDelta();
  if (accel.detectFall()){
    Serial.println("Patient has fallen");
  }
}
