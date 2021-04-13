#include <math.h>

const int B=4275; //valeur du thermistor
const int R=100000; //R0=100000kù
const int sensorpin=A0;

void setup() 
{
  Serial.begin(9600);

}

void loop() {
  int data=analogRead(sensorpin);
  float R1=1023.0/data-1.0;
  R1=R*R1;

  float temperatureF=1.0/(log(R1/R)/B+1/298.15)-273.15; //conversion en T°
  Serial.print(temperatureF);
  Serial.println("degres");

  delay(100);
  

}
