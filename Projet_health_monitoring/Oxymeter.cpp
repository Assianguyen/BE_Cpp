#include "Oxymeter.h"

//constructeur vide
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

//constructeur avec attributs
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

//setters
void Oxymeter::setAge(int yo){
  age = yo;
  maxValue = 206.9 - 0.67 * age;
}

void Oxymeter::setAgeDiz(int yoD){
  ageDiz = yoD;
}

void Oxymeter::setAgeUnit(int yoU){
  ageUnit = yoU;
}

//getters
int Oxymeter::getAge(){
  return age;
}

int Oxymeter::getAgeDiz(){
  return ageDiz;
}

int Oxymeter::getAgeUnit(){
  return ageUnit;
}

//calcule l'âge et la valeur max de BPM
void Oxymeter::calculateAge(){
  age = ageDiz * 10 + ageUnit;
  maxValue = 206.9 - 0.67 * age;
}

//set up de l'oxymètre
void Oxymeter::setUp(){
  //Serial.begin(9600);
}

//return la valeur lue par l'oxymètre
float Oxymeter::getValue(){
  return analogRead(numPort);
}

//vérifie les conditions de risques selon les valeurs de l'oxymètre
void Oxymeter::isAtRisk(float value){
  if((value >= maxValue) || (value <= minValue)){
    atRisk = true;
  } else {
    atRisk = false;
  }
}
