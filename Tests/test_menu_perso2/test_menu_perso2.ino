#include "Screens.h"
#include "Menu.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
 
//U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte buttons[] = {6,7,8}; //10 for additional pin
const byte nrButtons = 3; // change to 4 if additional button added

int ledMode = 0;
int buzzerMode = 0;
int ledPort = 9;
int buzzerPort = 10;
int lcdPort = 13;

unsigned long timer = (millis() / 10);
int age_diz;
int age_unit;

Menu welcome = Menu("     Welcome    ", WELCOME, nbWelcomeItems);
Menu goodbye = Menu("     Goodbye    ", GOODBYE, nbGoodbyeItems);
Menu ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, &doAgeMenuAction);
Menu subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, &doSubAgeAction);
Menu monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, &doMonitoringAction);
Menu settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, &doSettingsAction);
Menu yesNo = Menu(" Are you sure ? ", YES_NO_ITEMS, nbYesNoItems, &doYesNoAction);
Menu alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, &doAlarmAction);
Menu alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, &doAlarmHelpAction);
  
void setup() {
  
  //begin(uint8_t menu_select_pin, uint8_t menu_next_pin, uint8_t menu_prev_pin, uint8_t menu_up_pin, uint8_t menu_down_pin, uint8_t menu_home_pin)
  //u8g2.begin(7, U8X8_PIN_NONE, U8X8_PIN_NONE, 8, 6, U8X8_PIN_NONE);
 
  u8g2.begin();
  u8g2.setFont(u8g2_font_pressstart2p_8f);
  u8g2.firstPage();
  welcome.displayScreen();
  delay(2000);
  u8g2.clear();
  //displayMenu(ageMenu);
}

void loop() {
  /* Affiche le menu principal */
  u8g2.firstPage();
  monitoring.displayMenu();
}

/** Affiche le choix de l'utilisateur */
void doAgeMenuAction(byte selectedMenuItem) {
 
  switch(selectedMenuItem) {
  case 0:
    age_diz = 2;
    subAgeMenu.displayMenu();
    break;
 
  case 1:
    age_diz = 3;
    subAgeMenu.displayMenu();
    break;
 
  case 2:
    age_diz = 4;
    subAgeMenu.displayMenu();
    break;

  case 3:
    age_diz = 5;
    subAgeMenu.displayMenu();
    break;

  case 4:
    age_diz = 6;
    subAgeMenu.displayMenu();
    break;

  case 5:
    age_diz = 7;
    subAgeMenu.displayMenu();
    break;

  case 6:
    age_diz = 8;
    subAgeMenu.displayMenu();
    break;

  case 7:
    age_diz = 9;
    subAgeMenu.displayMenu();
    break;

  case 8:
    age_diz = 10;
    subAgeMenu.displayMenu();
    break;
  }
}

/** Affiche le choix de l'utilisateur */
void doSubAgeAction(byte selectedMenuItem) {
  switch(selectedMenuItem) {
  case 0:
    age_unit = 0;
    monitoring.displayMenu();
    break;
 
  case 1:
    age_unit = 1;
    monitoring.displayMenu();
    break;
 
  case 2:
    age_unit = 2;
    monitoring.displayMenu();
    break;

  case 3:
    age_unit = 3;
    monitoring.displayMenu();
    break;

  case 4:
    age_unit = 4;
    monitoring.displayMenu();
    break;

  case 5:
    age_unit = 5;
    monitoring.displayMenu();
    break;

  case 6:
    age_unit = 6;
    monitoring.displayMenu();
    break;

  case 7:
    age_unit = 7;
    monitoring.displayMenu();
    break;

  case 8:
    age_unit = 8;
    monitoring.displayMenu();
    break;
    
  case 9:
    age_unit = 9;
    monitoring.displayMenu();
    break;
  }
}
 
/** Affiche le choix de l'utilisateur */
void doMonitoringAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 7:
  //TURN ON ALARM
    digitalWrite(ledPort, HIGH);
    digitalWrite (buzzerPort, HIGH);
    u8g2.clear();
    alarmHelp.displayMenu();
    break;
 
  case 8:
     u8g2.clear();
    settings.displayMenu();
    break;

  case 9:
     u8g2.clear();
    yesNo.displayMenu();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doSettingsAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    ageMenu.displayMenu();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doYesNoAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    goodbye.displayScreen();
    break;

  case 6:
    monitoring.displayMenu();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doAlarmAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    digitalWrite(ledPort, LOW);
    digitalWrite (buzzerPort, LOW);
    monitoring.displayMenu();
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doAlarmHelpAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 10:
  //TURN OFF ALARM
    digitalWrite(ledPort, LOW);
    digitalWrite (buzzerPort, LOW);
    monitoring.displayMenu();
    break;
 }
}
