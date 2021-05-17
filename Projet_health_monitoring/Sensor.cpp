#include "Sensor.h"

//constructeur vide
Sensor::Sensor(){
	atRisk = false;
	minValue = 0.0;
	maxValue = 0.0;
}

//constructeur avec attributs
Sensor::Sensor(bool stateRisk, bool stateWarning, float min, float max, int port){
	atRisk = stateRisk;
  warning = stateWarning;
	minValue = min;
	maxValue = max;
 numPort = port;
}

//setters
void Sensor::setAtRisk(bool state){
  atRisk = state;
}

void Sensor::setWarning(bool state){
  warning = state;
}

//getters
float Sensor::getMinValue(){
	return minValue;
}

float Sensor::getMaxValue(){
	return maxValue;
}

bool Sensor::getAtRisk(){
  return atRisk;
}

bool Sensor::getWarning(){
  return warning;
}
