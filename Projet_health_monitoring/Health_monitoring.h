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

#include "Screens.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>

class Monitoring {
  
  protected :

    //variables de suivi du déclenchement de l'alarme

    //heure de déclenchement de l'alerte
    static unsigned long timeAlarm;
    //heure de déclenchement de l'alarme
    static unsigned long timeAlarmHelp;
    //heure de chute
    static unsigned long timeFallen;
    //envoie d'un message aux urgences pour chute
    static bool alarmFallen;

    //variables de suivi du menu actuel et du curseur

    //menu actuel
    static int actualMenu;
    //position du curseur
    static int cursorPosition;

    //variables des boutons

    //état du bouton up
    static byte pressedUp;
    //état du bouton down
    static byte pressedDown;
    //état du bouton select
    static byte pressedSelect;
    //état du bouton on/off
    static byte pressedOnOff;
    //aucun bouton pressé
    static int nonePressed; 

    //objets statiques pour les fonctions statiques
    static Led led; 
    static Buzzer buzzer;
    static Oxymeter oxy;
    static Sms message;

    //objets
    Switch upButton;
    Switch downButton;
    Switch selectButton;
    Switch onOffButton;
    Temperature temp;
    Accelerometer accelero;
    
    //menus statiques pour les fonctions statiques
    static Menu goodbye;
    static Menu blackScreen;

    //menus
    Menu welcome;
    Menu ageMenu;
    Menu subAgeMenu;
    Menu monitoring;
    Menu settings;
    Menu yesNo;
    Menu alarm;
    Menu alarmHelp;

    //varible this pour les fonctions statiques
    static Monitoring* This;

  public :

    //constructeurs
    Monitoring();
    Monitoring(Led lum,Buzzer buzz, Temperature thermo, Oxymeter oxym, Sms mess, Accelerometer accel);

    //méthodes
    void setUpMonitoring();
  	void startMonitoring();

    Menu getActualMenu();
  
    static void doAgeMenuAction(int selectedMenuItem);
    static void doSubAgeAction(int selectedMenuItem);
    static void doMonitoringAction(int selectedMenuItem);
    static void doSettingsAction(int selectedMenuItem);
    static void doYesNoAction(int selectedMenuItem);
    static void doAlarmAction(int selectedMenuItem);
    static void doAlarmHelpAction(int selectedMenuItem);

    //surchage d'opérateurs
    Monitoring operator++();
    Monitoring operator--();
};

#endif
