#include "Temperature.h"
#include <math.h>

//constructeurs
Temperature::Temperature()
{
  atRisk = false;
  warning = false;
  minValue = 36.0;
  warningTemp = 38.0;
  maxValue = 40.0;
  numPort = A0;
}

Temperature::Temperature(bool stateRisk, bool stateWarning, float min, float warnTemp, float max, int port)
{
  atRisk = stateRisk;
  warning = stateWarning;
  minValue = min;
  warningTemp = warnTemp;
  maxValue = max;
  numPort = port;
}

//méthodes
void Temperature::setUp(){
   Serial.begin(9600);
}

float Temperature::getValue(){
  int data=analogRead(numPort);
  int B=4275;
  int R=100000;
  float R1=1023.0/data-1.0;
  R1=R*R1;
  float temperature=1.0/(log(R1/R)/B+1/298.15)-273.15; //conversion en T°
  //Serial.print(temperature);
  //Serial.println("degres");
  return temperature;
}

void Temperature::isAtRisk(float value){
  if((value >= warningTemp) && (value < maxValue)) {
    warning = true;
  } else if((value >= maxValue) || (value < minValue)) {
    atRisk = true;
  } else {
    atRisk = false;
    warning = false;
  }
}
