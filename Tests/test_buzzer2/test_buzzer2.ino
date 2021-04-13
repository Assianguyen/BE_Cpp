 int frequency=1000; //Specified in Hz
 int buzzPin=5; 
 int timeOn=50; //specified in milliseconds
 int timeOff=50; //specified in millisecods


void setup(){


  
}


void loop(){
 
   tone(buzzPin, frequency);
   delay(timeOn);
   noTone(buzzPin);
   delay(timeOff);
}
