#ifndef MENU_H_
#define MENU_H_
 
#include <Arduino.h>
using namespace std;

enum BUTTON {
    BP_NONE,   // Aucun bouton appuyé
    BP_LEFT,   // Bouton gauche : retourner en arrière
    BP_RIGHT,  // Bouton droite : valider le choix
    BP_UP,     // Bouton haut : scroll vers le haut
    BP_DOWN    // Bouton bas : scroll vers le bas
};

class Menu {

protected :
    const char* prompt;     // Titre du menu
    const char** items;     // Tableau de choix du menu
    uint8_t nbItems;  // Nombre de choix possibles
    void (*callbackFnct)(uint8_t menuItemSelected); // Pointeur sur fonction pour gérer le choix de l'utilisateur

public :
  //constructeurs
  //Menu();

  Menu(const char* nom, const char** choix, uint8_t nbChoix, void (*function)(uint8_t selection));

  //methodes
  const char *getPrompt();

  const char *getSelectedItem(int selectedItem);

  const char **getItems();

  uint8_t getNbItems();

  void  getCallbackFnct(uint8_t selectedItem);
};
 
#endif /* MENU_H_ */
