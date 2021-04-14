#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

using namespace std;

class Alarm {
  
  protected :

    bool isOn;
    int numPort;

  public :

  //constructeurs
  Alarm();

  Alarm(bool state,int port);

  //fonctions annexes 

  void setState(bool state);
  void setPort(int port);

  bool getState();
  int getPort();

  virtual void turnOn()=0; //utilisée que par les classes filles
  virtual void turnOff()=0;
  virtual void setUp()=0;
  
  
  //destructeur
  
  };

#endif
