#ifndef MENU_H_
#define MENU_H_
 
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "Screens.h"

//définition de l'écran OLED
extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2;

class Menu{

  friend class Monitoring;

  protected :

    //titre du menu
    const char* prompt;

    //tableau de choix du menu
    const char** items;     

    //nombre de choix possibles
    int nbItems;  

    //numéro du premier choix possible
    int firstChoice;

    //numéro du dernier choix possible
    int lastChoice;

    //pointeur sur la fonction qui gère le choix de l'utilisateur
    void (*callbackFnct)(int menuItemSelected); 
    
  public :

    //constructeurs
    Menu();
    Menu(const char** choix, int nbChoix);
    Menu(const char* nom, const char** choix, int nbChoix, int first, int last, void (*function)(int selection));

    //méthodes  
    const char *getPrompt();
    const char *getSelectedItem(int selectedItem);
    const char **getItems();
    int getNbItems();
    int getLast();
    int getFirst();
    void  getCallbackFnct(int selectedItem);

    void displayScreen(int nMenu);
    void displayMenu(int cursorP);
    void displayMenuM(int cursorP, int age, int maxBpm, float temp, float accelero);
};
 
#endif
