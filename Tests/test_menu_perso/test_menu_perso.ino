#include <LiquidCrystal.h>
#include "Functions.h"
#include "Pitches.h"
#include "Symbols.h"
#include "Screens.h"
#include "Display.h"
#include "Menu.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
 
U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
int t;
byte pressedButton;

Menu ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, &doAgeMenuAction);
Menu subAgeMenu = Menu("Select:", SUB_AGE_ITEMS, nbSubAgeItems, &doSubAgeAction);
Menu monitoring = Menu("Health Monitoring",MONITORING_ITEMS, nbMonitoringItems, &doMonitoringAction);
Menu settings = Menu("Settings", SETTINGS_ITEMS, nbSettingsItems, &doSettingsAction);
Menu yesNo = Menu("Are you sure ?", YES_NO_ITEMS, nbYesNoItems, &doYesNoAction);
Menu alarm = Menu("Alarm activated", ALARM_ITEMS, nbAlarmItems, &doAlarmAction);
Menu alarmHelp = Menu("Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, &doAlarmHelpAction);
  
void setup() {
  

  /* Configuration du LCD */
  //lcd.begin(16, 2);
  u8g2.begin(buttons[1], U8X8_PIN_NONE, buttons[2], U8X8_PIN_NONE, buttons[0], U8X8_PIN_NONE);
  
  displayScreen(WELCOME, nbWelcomeItems);
  delay(2000);
  u8g2.clear();
  //displayMenu(ageMenu);
}

void loop() {
  /* Affiche le menu principal */
  displayMenu(monitoring);
}

// Look for a button press
byte checkButtonPress() {
  byte bP = 0;
  byte rBp = 0;
  for (t = 0; t<nrButtons;t++) {
    if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
  }
  rBp = bP;
  while (bP != 0) { // wait while the button is still down
    bP = 0;
    for (t = 0; t<nrButtons;t++) {
      if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
    }
  }
  return rBp;
}

/** Fonction retournant le bouton appuyé (s’il y en a un). */
BUTTON readPushButton(void) {
   pressedButton = checkButtonPress();

  if (pressedButton !=0) {
    switch (pressedButton) {
      case 1:
          return BP_LEFT; //RETURN
      break;
      case 2:
        return BP_RIGHT; //SELECT
      break;
      case 3:
       return BP_DOWN; //SCROLL DOWN
      break;
      case 4:
        return BP_UP; //SCROLL UP
      break;
    }
  } else {
    return BP_NONE; 
  }
}


/** Affiche le choix de l'utilisateur */
void displayScreen(const char** items, uint8_t nbItems) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_pressstart2p_8f);    
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+1)*10),items[i]);
    }
  } while ( u8g2.nextPage() );
  /* Affiche le choix de l'utilisateur */
//  lcd.clear();
//  for (int i = 0; i < nbItems; i++){
//    lcd.setCursor(i, 1);
//    lcd.print(items[i]);
//  }
}

/** Affiche le menu passé en argument */
void displayMenu(Menu &menu) {
 
  /* Variable pour le menu */
  byte selectedMenuItem = 0;   // Choix sélectionné
  byte shouldExitMenu = false; // Devient true quand l'utilisateur veut quitter le menu
  int8_t buttonPressed;      // Contient le bouton appuyé
 
  /* Tant que l'utilisateur ne veut pas quitter pas le menu */
  while(!shouldExitMenu) {
 
    /* Affiche le menu */
    //u8g2.clear();
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.firstPage();
    do {  
      u8g2.drawStr(0,10,menu.getPrompt());
      for (int i = 0; i < menu.getNbItems(); i++){
        u8g2.drawStr(0,((i+1)*10),menu.getSelectedItem(i));
      }
    } while ( u8g2.nextPage() );
    //lcd.print(menu.getPrompt());
    //lcd.setCursor(0, 1);
    //lcd.print(menu.getSelectedItem(selectedMenuItem));
 
//    /* Attend le relâchement du bouton */
//    while((buttonPressed = readPushButton()) != BP_NONE);
// 
//    /* Attend l'appui sur un bouton */
//    while((buttonPressed = readPushButton()) == BP_NONE);
// 
//    /* Anti rebond pour le bouton */
//    delay(30);
// 
//    /* Attend le relâchement du bouton */
//    while((buttonPressed = readPushButton()) != BP_NONE);
    do{
      buttonPressed = u8g2.getMenuEvent();
    } while(buttonPressed == 0);
 
    /* Gére l'appui sur le bouton */
    switch(buttonPressed) {
    case U8X8_MSG_GPIO_MENU_UP: // Bouton haut = choix précédent
 
      /* S'il existe un choix précédent */
      if(selectedMenuItem > 0) {
 
        /* Passe au choix précédent */
        selectedMenuItem--;
        u8g2.drawStr(0,((selectedMenuItem+1)*10),">");
        u8g2.drawStr(10,((selectedMenuItem+1)*10),menu.getSelectedItem(selectedMenuItem));
      }
      break;
 
    case U8X8_MSG_GPIO_MENU_DOWN: // Bouton bas = choix suivant
 
      /* S'il existe un choix suivant */
      if(selectedMenuItem < (menu.getNbItems() - 1)) {
 
        /* Passe au choix suivant */
        selectedMenuItem++;
        u8g2.drawStr(0,((selectedMenuItem+1)*10),">");
        u8g2.drawStr(10,((selectedMenuItem+1)*10),menu.getSelectedItem(selectedMenuItem));
      }
      break;
 
    case U8X8_MSG_GPIO_MENU_PREV: // Bouton gauche = sorti du menu
      shouldExitMenu = true;
      break;
 
    case U8X8_MSG_GPIO_MENU_SELECT:  // Bouton droit ou SELECT = validation du choix
      menu.getCallbackFnct(selectedMenuItem);
      break;
    }
  }
}

/** Affiche le choix de l'utilisateur */
void doAgeMenuAction(byte selectedMenuItem) {
 
  switch(selectedMenuItem) {
  case 0:
    age_diz = 2;
    displayMenu(subAgeMenu);
    break;
 
  case 1:
    age_diz = 3;
    displayMenu(subAgeMenu);
    break;
 
  case 2:
    age_diz = 4;
    displayMenu(subAgeMenu);
    break;

  case 3:
    age_diz = 5;
    displayMenu(subAgeMenu);
    break;

  case 4:
    age_diz = 6;
    displayMenu(subAgeMenu);
    break;

  case 5:
    age_diz = 7;
    displayMenu(subAgeMenu);
    break;

  case 6:
    age_diz = 8;
    displayMenu(subAgeMenu);
    break;

  case 7:
    age_diz = 9;
    displayMenu(subAgeMenu);
    break;

  case 8:
    age_diz = 10;
    displayMenu(subAgeMenu);
    break;
  }
}

/** Affiche le choix de l'utilisateur */
void doSubAgeAction(byte selectedMenuItem) {
  switch(selectedMenuItem) {
  case 0:
    age_unit = 0;
    displayMenu(monitoring);
    break;
 
  case 1:
    age_unit = 1;
    displayMenu(monitoring);
    break;
 
  case 2:
    age_unit = 2;
    displayMenu(monitoring);
    break;

  case 3:
    age_unit = 3;
    displayMenu(monitoring);
    break;

  case 4:
    age_unit = 4;
    displayMenu(monitoring);
    break;

  case 5:
    age_unit = 5;
    displayMenu(monitoring);
    break;

  case 6:
    age_unit = 6;
    displayMenu(monitoring);
    break;

  case 7:
    age_unit = 7;
    displayMenu(monitoring);
    break;

  case 8:
    age_unit = 8;
    displayMenu(monitoring);
    break;
    
  case 9:
    age_unit = 9;
    displayMenu(monitoring);
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
    displayMenu(alarmHelp);
    break;
 
  case 8:
    displayMenu(settings);
    break;

  case 9:
    displayMenu(yesNo);
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doSettingsAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    displayMenu(ageMenu);
    break;
 }
}

/** Affiche le choix de l'utilisateur */
void doYesNoAction(byte selectedMenuItem) {
 switch(selectedMenuItem) {
  case 5:
    displayScreen(GOODBYE, nbGoodbyeItems);
    break;

  case 6:
    displayMenu(monitoring);
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
    displayMenu(monitoring);
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
    displayMenu(monitoring);
    break;
 }
}
