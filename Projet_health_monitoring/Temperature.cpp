#include "Temperature.h"

//constructeur vide
Temperature::Temperature(){
  atRisk = false;
  warning = false;
  
  //réelle température minimale avant risque
  //minValue = 36.0;

  //pour la démo, valeur minimale fictive pour ne pas activer l'alarme trop de fois
  minValue = 0.0;
  warningTemp = 38.0;
  maxValue = 40.0;
  numPort = A0;
}

//constructeur avec attributs
Temperature::Temperature(bool stateRisk, bool stateWarning, float min, float warnTemp, float max, int port){
  atRisk = stateRisk;
  warning = stateWarning;
  minValue = min;
  warningTemp = warnTemp;
  maxValue = max;
  numPort = port;
}

//setter
void Temperature::setUp(){
   //Serial.begin(9600);
}

//getters
float Temperature::getValue(){

  //lecture de la valeur
  int data = analogRead(numPort);

  //conversion en degrés celsius
  int B = 4275;
  int R = 100000;
  float R1 = 1023.0 / data - 1.0;
  R1 = R * R1;
  float temperature = 1.0 / (log(R1 / R)/ B + 1 / 298.15) - 273.15;
  
  return temperature;
}

//renvoie si le patient est à risque
void Temperature::isAtRisk(float value){

  //si la température est comprise entre la température d'alerte et la température de risque
  if((value >= warningTemp) && (value < maxValue)){

    //il y a une alerte
    warning = true;

  //si la température est supérieure ou inférieure aux températures de risque
  }else if((value >= maxValue) || (value < minValue)){

    //il y a un risque
    atRisk = true;

  //sinon, tout va bien
  }else{
    atRisk = false;
    warning = false;
  }
}
