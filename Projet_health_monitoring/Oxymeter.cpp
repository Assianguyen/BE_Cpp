#include "Oxymeter.h"

//constructeurs
Oxymeter::Oxymeter(){
  atRisk = false;
  warning = false;
  minValue = 55.0;
  maxValue = 0.0;
  numPort = A0;
  ageDiz = 0;
  ageUnit = 0;
  age = 0;
}

Oxymeter::Oxymeter(bool stateRisk, bool stateWarning, float min, float max, int port, int yo){
  atRisk = stateRisk;
  warning = stateWarning;
  minValue = min;
  maxValue = max;
  numPort = port;
  ageDiz = 0;
  ageUnit = 0;
  age = yo;
}

//méthodes
void Oxymeter::setMaxValue(){
  maxValue = 206.9 - 0.67*age;
}

void Oxymeter::setAge(int yo){
  age = yo;
  maxValue = 206.9 - 0.67*age;
}

int Oxymeter::getAge(){
  return age;
}

void Oxymeter::setAgeDiz(int yoD){
  ageDiz = yoD;
}

int Oxymeter::getAgeDiz(){
  return ageDiz;
}

void Oxymeter::setAgeUnit(int yoU){
  ageUnit = yoU;
}

int Oxymeter::getAgeUnit(){
  return ageUnit;
}

void Oxymeter::calculateAge(){
  age = ageDiz*10+ageUnit;
  maxValue = 206.9 - 0.67*age;
}
    
void Oxymeter::setUp(){
  /*Serial.begin(9600);
  while(age<10 || age>100)
  {
    int l=0;
    char tampon[10]="";
    Serial.println("quel est votre age?");
    while(!l)
    {
      delay(200);
      l=Serial.available();
    }
    for (int i=0;i<l;i++)
    {
      tampon[i]=Serial.read();
      delay(15);
    }
    age=atof(tampon);
  }*/
}
    
float Oxymeter::getValue(){
  return analogRead(numPort);
}

void Oxymeter::isAtRisk(float value){
  if((value >= maxValue) || (value <= minValue)){
    atRisk = true;
  } else {
    atRisk = false;
  }
}
