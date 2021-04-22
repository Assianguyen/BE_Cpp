#include "Health_monitoring.h"

Monitoring monitor=Monitoring();

void setup() {
  // put your setup code here, to run once
  
  //méthode de setUpMonitoring
  monitor.setUpMonitoring();
}

void loop() {
  // put your main code here, to run repeatedly:
 
  monitor.startMonitoring();
}
