#include "Oxymeter.h"

Oxymeter::Oxymeter(){
  atRisk = false;
  warning = false;
  minValue = 55.0;
  maxValue = numeric_limits<float>::max();
  numPort = A0;
  age = 0.0;
}

Oxymeter::Oxymeter(bool stateRisk, bool stateWarning, float min, float max, int port, float yo){
  atRisk = stateRisk;
  warning = stateWarning;
  minValue = min;
  maxValue = max;
  numPort = port;
  age = yo;
}

void Oxymeter::setMaxValue(){
  maxValue = 206.9 - 0.67*age;
  Serial.print("Max value : ");
  Serial.println(maxValue);
}

void Oxymeter::setAge(float yo){
  age = yo;
  maxValue = 206.9 - 0.67*age;
  Serial.print("Max value : ");
  Serial.println(maxValue);
}

float Oxymeter::getAge(){
  return age;
}
    
void Oxymeter::setUp(){
  Serial.begin(9600);
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
  }
}
    
float Oxymeter::getValue(){
  Serial.print("BPM : ");
  Serial.println(analogRead(numPort));
  return analogRead(numPort);
}

void Oxymeter::isAtRisk(float value){
  if((value >= maxValue) || (value <= minValue)){
    atRisk = true;
  } else {
    atRisk = false;
  }
}
