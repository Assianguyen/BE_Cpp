#include "Health_monitoring.h"

//création d'un objet monitor qui contient tous les éléments de notre app (LED, buzzer, etc.)
Monitoring monitor = Monitoring();

void setup() {
  //set up du monitor
  monitor.setUpMonitoring();
}

void loop() {
  //fait tourner l'app
  monitor.startMonitoring();
}
