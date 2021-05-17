#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {

protected:

  int numPort;

public :

 virtual void setUp()=0;

};
#endif
