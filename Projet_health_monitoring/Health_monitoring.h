#ifndef HEALTH_MONITORING_H
#define HEALTH_MONITORING_H

#include "Buzzer.h"
#include "Led.h"
#include "Switch.h"
#include "Temperature.h"
#include "Oxymeter.h"
#include "Menu.h"
#include "Sms.h"
#include "Accelerometer.h"

#include <Arduino.h>

//extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2;

class Monitoring {
	
protected :

  /*
  static int age;
  static int age_diz;
  static int age_unit;
   */ 
  static int selectedOption;
  static int actualMenu;
  static int previousMenu;
  static int cursorPosition;
    
  static byte pressedUp;
  static byte pressedDown;
  static byte pressedSelect;
  static byte pressedReturn;
  //static byte pressedOnOff;
  static int nonePressed; 

  static Led led1; //objet LED
  static Buzzer buzzer1;
  Switch upButton;
  Switch downButton;
  Switch selectButton;
  //Switch onOffButton;
  Temperature temp1;
  Accelerometer accel1;
  static Oxymeter oxy1;
  static Sms message;
  
  Menu welcome;
  //static Menu goodbye;
  Menu ageMenu;
  Menu subAgeMenu;
  Menu monitoring;
  Menu settings;
  //Menu yesNo;
  Menu alarm;
  Menu alarmHelp;

  static Monitoring* This;

public :

  //constructeurs
  Monitoring();
  Monitoring(Led lum,Buzzer buzz, Temperature thermo, Oxymeter oxym, Sms mess, Accelerometer accel);

  //méthodes
  void setUpMonitoring();
	void startMonitoring();

  Menu getActualMenu();
  void setActualMenu(int actualM);

  Menu getPreviousMenu();
  void setPreviousMenu(int previousM);
  
  static void doAgeMenuAction(int selectedMenuItem);
  static void doSubAgeAction(int selectedMenuItem);
  static void doMonitoringAction(int selectedMenuItem);
  static void doSettingsAction(int selectedMenuItem);
  static void doYesNoAction(int selectedMenuItem);
  static void doAlarmAction(int selectedMenuItem);
  static void doAlarmHelpAction(int selectedMenuItem);
};

#endif
