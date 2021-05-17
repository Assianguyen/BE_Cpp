#include "Accelerometer.h"

uint8_t Accelerometer::sensorAddress = 0;   //adresse du I2C : 0x18

//constructeur vide
Accelerometer::Accelerometer(){
  atRisk = false;
  sensorAddress = 0;
  nbSample = 0;
}

//constructeur avec attributs
Accelerometer::Accelerometer(bool isFalling, uint8_t address, int echantillon){
  atRisk = isFalling;
  sensorAddress = address;
  nbSample = echantillon;
}

//set up de l'accéléromètre
void Accelerometer::setUp(){
  Wire.begin(sensorAddress);

  //Equipment connection exception or I2C address error
  while(init() == -1){  
    delay(1000);
  }
}

//écrit à une adresse spécifique un tableau de valeurs
uint8_t Accelerometer::writeTab(uint8_t address, uint8_t *tabvalue, size_t tabsize, bool autoIncrement){   
  Wire.beginTransmission(sensorAddress);
  if(autoIncrement){
    Wire.write(address);
    Wire.write(tabvalue, tabsize);
  }else{
    for(size_t i = 0; i < tabsize; i++){
      Wire.write(address + i);
      Wire.write(tabvalue[i]);
      if(i < (tabsize-1)){
        Wire.endTransmission(false);
        Wire.beginTransmission(sensorAddress);
      }
    }
  }
  return Wire.endTransmission(true);
}

//initialisation de l'accéléromètre
int8_t Accelerometer::init(){
  int8_t ret = 0;

  //test de connexion avec le protocole I2C
  Wire.beginTransmission(sensorAddress);
  ret = Wire.endTransmission();
  if(ret != 0){
    
    //return -1 si pas de connexion
    ret = -1;
  }else{
    uint8_t ctrl_reg_values[] = {0x2F, 0x00, 0x00,0x30,0x00, 0x00}; 
    ret = (int8_t)writeTab(0xA0, ctrl_reg_values, sizeof(ctrl_reg_values));
  }
  return ret;
}

//crée et remplit un tableau avec les valeurs de l'accélération en x, y et z
void Accelerometer::fillTab(uint8_t address, uint8_t *tabvalue, uint8_t tabsize, bool autoIncrement){   
  address = 0x80 | address;
  if(autoIncrement){
    Wire.beginTransmission(sensorAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(sensorAddress, tabsize);
    for(uint8_t i = 0; i < tabsize; i++){
      tabvalue[i] = Wire.read();
    }
  }else{
    for(uint8_t i = 0; i < tabsize; i++){
      Wire.beginTransmission(sensorAddress);
      Wire.write(address + i);
      Wire.endTransmission();
      Wire.requestFrom(sensorAddress, (uint8_t)1);
      tabvalue[i] = Wire.read();
    }
  }  
}

//return la valeur (convertie en mg) d'accélération en z
float Accelerometer::getValue(){
  uint8_t sensorData[6];
  fillTab(0xA8, sensorData, 6);
  int16_t zBrut = ((int8_t)sensorData[5]) * 256 + sensorData[4];
  int16_t z = (int32_t)zBrut * 1000 / (1024 * 2);
  return z;
}

//calcule la moyenne d'accélération en z d'un échantillon de taille variable (initialisée à 50)
int16_t Accelerometer::calculateMean(){
  int16_t meanValue;
  int16_t sum = 0;
  for (int i = 0; i < nbSample; i++){
    sum = sum + abs(getValue());
  }
  meanValue = sum/nbSample;
  return meanValue;
}

//calcule l'écart à partir duquel on considère que le patient est tombé
int16_t Accelerometer::calculateDelta(){
  int16_t deltaValue = abs(1.5*calculateMean());
  return deltaValue;
}

//vérifie les conditions de chute
void Accelerometer::isAtRisk(float value){
  
  //récupère la current value
  value = abs(getValue());
  int16_t mean = calculateMean();

  //condition de chute : 
  //écart entre la valeur actuelle et la moyenne supérieur à delta, 
  //si la valeur et la moyenne ne sont pas à 0 
  if((abs(value-mean) > calculateDelta()) && (value != 0) && (mean != 0)){
    atRisk = true;    
  }else{
    atRisk = false;
  }  
}
