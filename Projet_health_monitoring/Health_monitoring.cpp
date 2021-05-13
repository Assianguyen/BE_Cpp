#include "Health_monitoring.h"
#include "Screens.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

//extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
/*
int Monitoring::age = 0;
int Monitoring::age_diz = 0;
int Monitoring::age_unit = 0;
*/
int Monitoring::selectedOption = 0;
int Monitoring::actualMenu = nAge;
//int Monitoring::previousMenu = nAge;
int Monitoring::cursorPosition = firstAge;

byte Monitoring::pressedUp = 0;
byte Monitoring::pressedDown = 0;
byte Monitoring::pressedSelect = 0;
int Monitoring::nonePressed = 1;
Monitoring* Monitoring::This = 0;

//Led Monitoring::led1 = Led(false,D3); //objet LED
//Buzzer Monitoring::buzzer1 = Buzzer(false,D7);
//Oxymeter Monitoring::oxy1 = Oxymeter(false,false,55.0, 200.0,A0,0.0);

Led Monitoring::led1 = Led(false,9); //objet LED
Buzzer Monitoring::buzzer1 = Buzzer(false,10);
Oxymeter Monitoring::oxy1 = Oxymeter(false,false,55.0, 200.0,A0,0);

Monitoring::Monitoring(){
//    led1 = Led(false,D3);
//    buzzer1 = Buzzer(false,D7);
//    upButton = Switch(false,D4);
//    downButton = Switch(false,D6);
//    selectButton = Switch(false,D5);
//    temp1 = Temperature(false, false, 36.0,38.0,40.0,A0);
//    oxy1 = Oxymeter(false,false,55.0, 200.0,A0,0.0);
//    led1 = Led(false,9);
//    buzzer1 = Buzzer(false,10);
    This = this;
    upButton = Switch(false,8);
    downButton = Switch(false,6);
    selectButton = Switch(false,7);
    temp1 = Temperature(false, false, 36.0,38.0,40.0,A0);
    //oxy1 = Oxymeter(false,false,55.0, 200.0,A0,0.0);
    welcome = Menu(WELCOME, nbWelcomeItems);
    //goodbye = Menu(GOODBYE, nbGoodbyeItems);
    ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, firstAge, lastAge, &doAgeMenuAction);
    subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, firstSubAge, lastSubAge, &doSubAgeAction);
    monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, firstMonitoring, lastMonitoring, &doMonitoringAction);
    settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, firstSettings, lastSettings, &doSettingsAction);
    //yesNo = Menu(" Are you sure ? ", YES_NO_ITEMS, nbYesNoItems, firstYesNo, lastYesNo, &doYesNoAction);
    alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, firstAlarm, lastAlarm, &doAlarmAction);
    alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, firstAlarmHelp, lastAlarmHelp, &doAlarmHelpAction);
}

Monitoring::Monitoring(Led lum,Buzzer buzz, Temperature thermo,Oxymeter oxym){
    This = this;
    led1 = lum;
    buzzer1 = buzz;
    temp1 = thermo;
    oxy1 = oxym;/*
    welcome = Menu(WELCOME, nbWelcomeItems);
    goodbye = Menu(GOODBYE, nbGoodbyeItems);
    ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, firstAge, lastAge, prevAgeMenu, &Monitoring::doAgeMenuAction);
    subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, firstSubAge, lastSubAge, prevSubAge, &Monitoring::doSubAgeAction);
    monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, firstMonitoring, lastMonitoring, prevMonitoring, &Monitoring::doMonitoringAction);
    settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, firstSettings, lastSettings, prevSettings, &Monitoring::doSettingsAction);
    yesNo = Menu(" Are you sure ? ", YES_NO_ITEMS, nbYesNoItems, firstYesNo, lastYesNo, prevYesNo, &Monitoring::doYesNoAction);
    alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, firstAlarm, lastAlarm, prevAlarm, &Monitoring::doAlarmAction);
    alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, firstAlarmHelp, lastAlarmHelp, prevAlarmHelp, &Monitoring::doAlarmHelpAction);
*/
}

void Monitoring::setUpMonitoring(){
  led1.setUp(); 
  buzzer1.setUp();
  upButton.setUp();
  downButton.setUp();
  selectButton.setUp();
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

  if(pressedUp == HIGH){
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
    //this->getActualMenu().displayMenuM(cursorPosition, age_diz, age_unit);
    this->getActualMenu().displayMenuM(cursorPosition, oxy1.getAgeDiz(), oxy1.getAgeUnit());
  } else {
    this->getActualMenu().displayMenu(cursorPosition);
  }
  
/*  
  temp1.isAtRisk(temp1.getValue());
  
  if(temp1.getWarning() || temp1.getAtRisk()){
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = nAlarm;
    cursorPosition = temp.getActualMenu().getFirst();
    
    if(temp1.getAtRisk()){
      u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = nAlarmHelp;
    cursorPosition = temp.getActualMenu().getFirst();
    }
    
  }*/
  
  //delay(500);
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
      case 5:
        return yesNo;
      break;
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
/*
Menu Monitoring::getPreviousMenu(){
  switch(previousMenu){
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
      case 5:
        return yesNo;
      break;
      case 6:
        return alarm;
      break;
      case 7:
        return alarmHelp;
      break;
  }
}

void Monitoring::setPreviousMenu(int previousM){
  previousMenu = previousM;
}
*/
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

/*
void Monitoring::doYesNoAction(int selectedMenuItem) {
  int t;
  Monitoring temp = Monitoring(t);
 switch(selectedMenuItem) {
  case 5:
    goodbye.displayScreen();
    //delay(2000);
    break;

  case 6:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = nMonitoring;
    cursorPosition = temp.getActualMenu().getFirst();
    break;
 }
}*/

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
