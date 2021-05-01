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
    int nbItems;  // Nombre de choix possibles
    int firstChoice;
    int lastChoice;
    int prevMenu;
    void (*callbackFnct)(int menuItemSelected); // Pointeur sur fonction pour gérer le choix de l'utilisateur

public :
  //constructeurs
  //Menu();
  Menu(const char* nom, const char** choix, int nbChoix);
  Menu(const char* nom, const char** choix, int nbChoix, int first, int last, int prev, void (*function)(int selection));

  //methodes
  const char *getPrompt();

  const char *getSelectedItem(int selectedItem);

  const char **getItems();

  int getNbItems();

  int getLast();
  
  int getFirst();

  int getPrev();

  void  getCallbackFnct(int selectedItem);

  void displayScreen();

  void displayMenu(int cursorP);
};
 
#endif /* MENU_H_ */
