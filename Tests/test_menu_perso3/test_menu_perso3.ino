#include "Screens.h"
#include "Menu.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

//const int nbButtons = 3;

//const int selectPin = 7;
//const int upPin  = 8;
//const int downPin = 6;
//const int downPin = 5;
//const int ledPin = 9;
//const int buzzerPin = 10;
//
//const int nAge = 1;
//const int nSubAge = 2;
//const int nMonitoring = 3;
//const int nSettings = 4;
//const int nYesNo = 5;
//const int nAlarm = 6;
//const int nAlarmHelp = 7;
 
//U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

static int age = 0;
static int age_diz = 0;
static int age_unit = 0;

static int selectedOption = 0;
static int actualMenu = 1;
static int previousMenu = 1;
static int cursorPosition = 1;

static byte pressedUp = 0;
static byte pressedDown = 0;
static byte pressedSelect = 0;
static byte pressedReturn = 0;
static int nonePressed = 1;

Menu welcome = Menu("     Welcome    ", WELCOME, nbWelcomeItems);
Menu goodbye = Menu("     Goodbye    ", GOODBYE, nbGoodbyeItems);
Menu ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, firstAge, lastAge, prevAgeMenu, &doAgeMenuAction);
Menu subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, firstSubAge, lastSubAge, prevSubAge, &doSubAgeAction);
Menu monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, firstMonitoring, lastMonitoring, prevMonitoring, &doMonitoringAction);
Menu settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, firstSettings, lastSettings, prevSettings, &doSettingsAction);
Menu yesNo = Menu(" Are you sure ? ", YES_NO_ITEMS, nbYesNoItems, firstYesNo, lastYesNo, prevYesNo, &doYesNoAction);
Menu alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, firstAlarm, lastAlarm, prevAlarm, &doAlarmAction);
Menu alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, firstAlarmHelp, lastAlarmHelp, prevAlarmHelp, &doAlarmHelpAction);

//Menu welcome = Menu("     Welcome    ", WELCOME, 11);
//Menu goodbye = Menu("     Goodbye    ", GOODBYE, 11);
//Menu ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, 11, 0, 10, &doAgeMenuAction);
//Menu subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, 10, 0, 9, &doSubAgeAction);
//Menu monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, 10, 7, 9, &doMonitoringAction);
//Menu settings = Menu("    Settings    ", SETTINGS_ITEMS, 11, 5, 5, &doSettingsAction);
//Menu yesNo = Menu(" Are you sure ? ", YES_NO_ITEMS, 11, 5, 6, &doYesNoAction);
//Menu alarm = Menu(" Alarm activated", ALARM_ITEMS, 11, 10, 10, &doAlarmAction);
//Menu alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, 11, 10, 10, &doAlarmHelpAction);
  
void setup() {
  
  //begin(uint8_t menu_select_pin, uint8_t menu_next_pin, uint8_t menu_prev_pin, uint8_t menu_up_pin, uint8_t menu_down_pin, uint8_t menu_home_pin)
  //u8g2.begin(7, U8X8_PIN_NONE, U8X8_PIN_NONE, 8, 6, U8X8_PIN_NONE);
  //Serial.begin(9600); 
  //Serial.println("Setup");
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_pressstart2p_8f);
  u8g2.firstPage();
  welcome.displayScreen();
  delay(2000);
  u8g2.clear();
}

void loop() {
  u8g2.firstPage();
  checkButton();
  updateMenu();
}

void checkButton(){
  pressedUp = digitalRead(8);
  pressedDown = digitalRead(6);
  pressedSelect = digitalRead(7);
  //pressedReturn = digitalRead(5);

  if(pressedUp == HIGH){
    if(cursorPosition>=getActualMenu().getFirst()){
      cursorPosition--; 
      nonePressed = 0;
      do{
        //CHANGER LE SURLIGNAGE
        u8g2.setDrawColor(1);
        u8g2.drawBox(0, (cursorPosition+1)*10, 140, 20);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0, (cursorPosition+2)*10, getActualMenu().getSelectedItem(cursorPosition)); 
      } while( u8g2.nextPage() );     
    }
  } else if(pressedDown == HIGH){
    if(cursorPosition<=getActualMenu().getLast()){
      cursorPosition++;  
      nonePressed = 0;
      do{
        u8g2.setDrawColor(1);
        u8g2.drawBox(0, (cursorPosition+1)*10, 140, 20);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0, (cursorPosition+2)*10, getActualMenu().getSelectedItem(cursorPosition)); 
      } while( u8g2.nextPage() );   
    }
  } else if(pressedSelect == HIGH){
    getActualMenu().getCallbackFnct(cursorPosition);
    nonePressed = 0;
  } else if(pressedReturn == HIGH){
    previousMenu = actualMenu;
    actualMenu = getActualMenu().getPrev();
    nonePressed = 0;
  }else {
    nonePressed = 1;
  }  
}

void updateMenu(){
 getActualMenu().displayMenu();
 do{
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, (cursorPosition+1)*10, 140, 20);
  u8g2.setDrawColor(2);
  u8g2.drawStr(0, (cursorPosition+2)*10, getActualMenu().getSelectedItem(cursorPosition)); 
  } while( u8g2.nextPage() );
  
  //Serial.println("Age : "+age);
}

Menu getActualMenu(){
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

/** Affiche le choix de l'utilisateur */
void doAgeMenuAction(int selectedMenuItem) {
 
  switch(selectedMenuItem) {
  case 0:
    age_diz = 1;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;
 
  case 1:
    age_diz = 2;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;
 
  case 2:
    age_diz = 3;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;    
    cursorPosition = getActualMenu().getFirst();
    break;

  case 3:
    age_diz = 4;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 4:
    age_diz = 5;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 5:
    age_diz = 6;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 6:
    age_diz = 7;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 7:
    age_diz = 8;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 8:
    age_diz = 9;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 9:
    age_diz = 10;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 10:
    age_diz = 11;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 2;
    cursorPosition = getActualMenu().getFirst();
    break;
  }
}

/** Affiche le choix de l'utilisateur */
void doSubAgeAction(int selectedMenuItem) {
  switch(selectedMenuItem) {
  case 0:
    age_unit = 0;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
 
  case 1:
    age_unit = 1;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
 
  case 2:
    age_unit = 2;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 3:
    age_unit = 3;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 4:
    age_unit = 4;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 5:
    age_unit = 5;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 6:
    age_unit = 6;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 7:
    age_unit = 7;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 8:
    age_unit = 8;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
    
  case 9:
    age_unit = 9;
    age = age_diz*10+age_unit;
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
  }
}
 
/** Affiche le choix de l'utilisateur */
void doMonitoringAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 7:
  //TURN ON ALARM
    digitalWrite(9, HIGH);
    digitalWrite (10, HIGH);
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 7;
    cursorPosition = getActualMenu().getFirst();
    break;
 
  case 8:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 4;
    cursorPosition = getActualMenu().getFirst();
    break;

  case 9:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 5;
    cursorPosition = getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doSettingsAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 1;
    cursorPosition = getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doYesNoAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    goodbye.displayScreen();
    //delay(2000);
    break;

  case 6:
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doAlarmAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    digitalWrite(9, LOW);
    digitalWrite (10, LOW);
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doAlarmHelpAction(int selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    digitalWrite(9, LOW);
    digitalWrite (10, LOW);
    u8g2.clear();
    previousMenu = actualMenu;
    actualMenu = 3;
    cursorPosition = getActualMenu().getFirst();
    break;
 }
}