#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

using namespace std;

class Alarm {

  protected :

    bool alarmOn;

  public :

  //constructeurs
  Alarm();

  Alarm(bool state);

  //fonctions annexes 

  void setAlarmOn(bool state);

  bool isAlarmOn();
  
  //destructeur
  
  };

#endif
