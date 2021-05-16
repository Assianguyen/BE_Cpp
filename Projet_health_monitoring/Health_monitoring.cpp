#include "Health_monitoring.h"
#include "Screens.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define DELAY_10_MIN 600000000

unsigned long Monitoring::timeAlarm = 0;
unsigned long Monitoring::timeAlarmHelp = 0;

int Monitoring::selectedOption = 0;
int Monitoring::actualMenu = nAge;
int Monitoring::cursorPosition = firstAge;

byte Monitoring::pressedUp = 0;
byte Monitoring::pressedDown = 0;
byte Monitoring::pressedSelect = 0;
//byte Monitoring::pressedOnOff = 0;
int Monitoring::nonePressed = 1;
Monitoring* Monitoring::This = 0;

Led Monitoring::led1 = Led(false,D8); //objet LED
Buzzer Monitoring::buzzer1 = Buzzer(false,D9);
Oxymeter Monitoring::oxy1 = Oxymeter(false,false,55.0, 200.0,A0,0.0);
Sms Monitoring::message = Sms(80);

//Menu Monitoring::goodbye = Menu(GOODBYE, nbGoodbyeItems);

Monitoring::Monitoring(){
      upButton = Switch(false,D12);
      selectButton = Switch(false,D11);
      downButton = Switch(false,D10);
     // onOffButton = Switch(false,14);
    This = this;
    temp1 = Temperature(false, false, 0.0,38.0,40.0,A0);
    accel1=Accelerometer(false, 0x18, 50);
    welcome = Menu(WELCOME, nbWelcomeItems);
    //goodbye = Menu(GOODBYE, nbGoodbyeItems);
    ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, firstAge, lastAge, &doAgeMenuAction);
    subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, firstSubAge, lastSubAge, &doSubAgeAction);
    monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, firstMonitoring, lastMonitoring, &doMonitoringAction);
    settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, firstSettings, lastSettings, &doSettingsAction);
    //yesNo = Menu("   Turn off ?   ", YES_NO_ITEMS, nbYesNoItems, firstYesNo, lastYesNo, &doYesNoAction);
    alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, firstAlarm, lastAlarm, &doAlarmAction);
    alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, firstAlarmHelp, lastAlarmHelp, &doAlarmHelpAction);
}

Monitoring::Monitoring(Led lum,Buzzer buzz, Temperature thermo,Oxymeter oxym, Sms mess, Accelerometer accel){
    This = this;
    led1 = lum;
    buzzer1 = buzz;
    temp1 = thermo;
    oxy1 = oxym;
    message = mess;
    accel1=accel;
}

void Monitoring::setUpMonitoring(){
  led1.setUp(); 
  accel1.setUp();
  buzzer1.setUp();
  upButton.setUp();
  downButton.setUp();
  selectButton.setUp();
  //onOffButton.setUp();
  message.setUp();
  //temp1.setUp();
  //oxy1.setUp();
  u8g2.begin();
  u8g2.setFont(u8g2_font_pressstart2p_8f);
  u8g2.firstPage();
  welcome.displayScreen();
  delay(2000);
  u8g2.clear();
}

void Monitoring::startMonitoring()
{
  //fonction checkButton
  pressedUp = upButton.getValue();
  pressedDown = downButton.getValue();
  pressedSelect = selectButton.getValue();
//  pressedOnOff = onOffButton.getValue();

  /*if(pressedOnOff == HIGH){
    //actualMenu = nYesNo;
    nonePressed = 0;
  } else*/ if(pressedUp == HIGH){
    if(cursorPosition>this->getActualMenu().getFirst()){
      cursorPosition--; 
      nonePressed = 0;   
    }
  } else if(pressedDown == HIGH){
    if(cursorPosition<this->getActualMenu().getLast()){
      cursorPosition++;  
      nonePressed = 0;
    }
  } else if(pressedSelect == HIGH){
    this->getActualMenu().getCallbackFnct(cursorPosition);
    nonePressed = 0;
  }else {
    nonePressed = 1;
  }  

  //fonction updateMenu
  u8g2.firstPage();  
  if (actualMenu == nMonitoring){
    this->getActualMenu().displayMenuM(cursorPosition, oxy1.getAge(), oxy1.getMaxValue(), temp1.getValue());
  } else {
    this->getActualMenu().displayMenu(cursorPosition);
  } 
  temp1.isAtRisk(temp1.getValue());

  if((micros()>(timeAlarm+DELAY_10_MIN)) || (timeAlarm == 0)){
    if(temp1.getWarning()){
      timeAlarm = micros();
      actualMenu = nAlarm;
      cursorPosition = this->getActualMenu().getFirst();
      led1.turnOn();
      buzzer1.turnOn();
    }
  }

  if((micros()>(timeAlarmHelp+DELAY_10_MIN)) || (timeAlarmHelp == 0)){
    if(temp1.getAtRisk()){
      timeAlarmHelp = micros();
      actualMenu = nAlarmHelp;
      cursorPosition = this->getActualMenu().getFirst();
      message.sendEvent("alarm_on");
      led1.turnOn();
      buzzer1.turnOn();
    }
  }
}

Menu Monitoring::getActualMenu(){
  switch(actualMenu){
      case 1:
        return ageMenu;
      break;
      case 2:
        return subAgeMenu;
      break;
      case 3:
        return monitoring;
      break;
      case 4:
        return settings;
      break;
      /*case 5:
        return yesNo;
      break;*/
      case 6:
        return alarm;
      break;
      case 7:
        return alarmHelp;
      break;
  }
}

void Monitoring::setActualMenu(int actualM){
  actualMenu = actualM;
}

void Monitoring::doAgeMenuAction(int selectedMenuItem) {
  switch(selectedMenuItem) {
  case 0:
    oxy1.setAgeDiz(1);
    //age_diz = 1;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
  case 1:
    oxy1.setAgeDiz(2);
    //age_diz = 2;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
  case 2:
    oxy1.setAgeDiz(3);
    //age_diz = 3;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;    
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 3:
    oxy1.setAgeDiz(4);
    //age_diz = 4;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 4:
    oxy1.setAgeDiz(5);
    //age_diz = 5;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 5:
    oxy1.setAgeDiz(6);
    //age_diz = 6;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 6:
    oxy1.setAgeDiz(7);
    //age_diz = 7;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 7:
    oxy1.setAgeDiz(8);
    //age_diz = 8;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 8:
    oxy1.setAgeDiz(9);
    //age_diz = 9;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 9:
    oxy1.setAgeDiz(10);
    //age_diz = 10;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 10:
    oxy1.setAgeDiz(11);
    //age_diz = 11;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

/** Affiche le choix de l'utilisateur */
void Monitoring::doSubAgeAction(int selectedMenuItem) {
  switch(selectedMenuItem) {
  case 0:
    oxy1.setAgeUnit(0);
    oxy1.calculateAge();
    //age_unit = 0;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
  case 1:
    oxy1.setAgeUnit(1);
    oxy1.calculateAge();
    //age_unit = 1;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
  case 2:
    oxy1.setAgeUnit(2);
    oxy1.calculateAge();
    //age_unit = 2;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 3:
    oxy1.setAgeUnit(3);
    oxy1.calculateAge();
    //age_unit = 3;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 4:
    oxy1.setAgeUnit(4);
    oxy1.calculateAge();
    //age_unit = 4;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 5:
    oxy1.setAgeUnit(5);
    oxy1.calculateAge();
    //age_unit = 5;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 6:
    oxy1.setAgeUnit(6);
    oxy1.calculateAge();
    //age_unit = 6;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 7:
    oxy1.setAgeUnit(7);
    oxy1.calculateAge();
    //age_unit = 7;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

  case 8:
    oxy1.setAgeUnit(8);
    oxy1.calculateAge();
    //age_unit = 8;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
    
  case 9:
    oxy1.setAgeUnit(9);
    oxy1.calculateAge();
    //age_unit = 9;
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}
 
/** Affiche le choix de l'utilisateur */
void Monitoring::doMonitoringAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 8:
  //TURN ON ALARM
    message.sendEvent("alarm_on");
    led1.turnOn();
    buzzer1.turnOn();
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nAlarmHelp;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
  case 9:
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nSettings;
    cursorPosition = This->getActualMenu().getFirst();
    break;
/*
  case 9:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = nYesNo;
    cursorPosition = temp.getActualMenu().getFirst();
    break;*/
 }
}

/** Affiche le choix de l'utilisateur */
void Monitoring::doSettingsAction(int selectedMenuItem) {
  //int t;
  //Monitoring temp = Monitoring(t);
 switch(selectedMenuItem) {
  case 5:
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  case 6:
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 }
}

void Monitoring::doYesNoAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    //goodbye.displayScreen();
    //delay(2000);
    break;

  case 6:
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void Monitoring::doAlarmAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    led1.turnOff();
    buzzer1.turnOff();
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void Monitoring::doAlarmHelpAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    led1.turnOff();
    buzzer1.turnOff();
    u8g2.clear();
    //previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 }
}
