#include "Health_monitoring.h"

//création d'un objet monitor qui contient tous les éléments de notre app (LED, buzzer, etc.)
Monitoring moniteur = Monitoring();

void setup() {
  //set up du moniteur
  moniteur.setUpMonitoring();
}

void loop() {
  //fait tourner l'app
  moniteur.startMonitoring();
}
