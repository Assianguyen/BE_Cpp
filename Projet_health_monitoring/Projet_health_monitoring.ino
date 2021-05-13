#include "Health_monitoring.h"

Monitoring monitor = Monitoring();

void setup() {
  monitor.setUpMonitoring();
}

void loop() {
  monitor.startMonitoring();
}
