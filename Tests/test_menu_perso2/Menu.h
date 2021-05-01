#ifndef MENU_H_
#define MENU_H_
 
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
using namespace std;

extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2;

class Menu {

protected :
    const char* prompt;     // Titre du menu
    const char** items;     // Tableau de choix du menu
    uint8_t nbItems;  // Nombre de choix possibles
    void (*callbackFnct)(uint8_t menuItemSelected); // Pointeur sur fonction pour gérer le choix de l'utilisateur

public :
  //constructeurs
  //Menu();
  Menu(const char* nom, const char** choix, uint8_t nbChoix);
  Menu(const char* nom, const char** choix, uint8_t nbChoix, void (*function)(uint8_t selection));

  //methodes
  const char *getPrompt();

  const char *getSelectedItem(int selectedItem);

  const char **getItems();

  uint8_t getNbItems();

  void  getCallbackFnct(uint8_t selectedItem);

  void displayScreen();

  void displayMenu();
};
 
#endif /* MENU_H_ */
