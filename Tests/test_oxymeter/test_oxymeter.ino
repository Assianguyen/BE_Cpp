#define heartratePin A0
#include"DFRobot_Heartrate.h"

DFRobot_Heartrate heartrate(ANALOG_MODE);

///< ANALOG_MODE or DIGITAL_MODE
void setup(){  
  Serial.begin(115200);
  }
  
 void loop(){
    uint8_t rateValue;
    heartrate.getValue(heartratePin);///< A1 foot sampled values  
    rateValue = heartrate.getRate();///< Get heart rate value 
    if(rateValue!=0){    
      Serial.println("BPM = ");
      Serial.println(rateValue);
      }
      delay(20);
  }
