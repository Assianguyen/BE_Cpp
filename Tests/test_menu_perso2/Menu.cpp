#include "Menu.h"
#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

Menu::Menu(const char* nom, const char** choix, uint8_t nbChoix)
{
  prompt = nom;
  items = choix;
  nbItems = nbChoix;
  //callbackFnct = null;
}

Menu::Menu(const char* nom, const char** choix, uint8_t nbChoix, void (*function)(uint8_t selection))
{
	prompt = nom;
  items = choix;
  nbItems = nbChoix;
  callbackFnct = function;
}

const char *Menu::getPrompt(){
  return prompt;
}

const char *Menu::getSelectedItem(int selectedItem){
  return items[selectedItem];
}

const char **Menu::getItems(){
  return items;
}

uint8_t Menu::getNbItems(){
  return nbItems;
}

void Menu::getCallbackFnct(uint8_t selectedItem){
  callbackFnct(selectedItem);
}

void Menu::displayScreen() {
  //u8g2.firstPage();
  do {
    //u8g2.setFont(u8g2_font_pressstart2p_8f);    
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+1)*10),items[i]);
    }
  } while ( u8g2.nextPage() );
}

void Menu::displayMenu() {
 
  /* Variable pour le menu */
  static byte selectedMenuItem = 0;   // Choix sélectionné
  byte shouldExitMenu; // Devient true quand l'utilisateur veut quitter le menu
  int8_t buttonPressed;      // Contient le bouton appuyé

  int t;
  byte pressedButton = 0;
  byte pressedUp = 0;
  byte pressedDown = 0;
  byte pressedSelect = 0;

//  if(!shouldExitMenu){
//    do {  
//        u8g2.drawStr(0,10,prompt);
//        for (int i = 0; i < nbItems; i++){
//          u8g2.drawStr(0,((i+2)*10),items[i]);
//        }
//      } while ( u8g2.nextPage() );
//      shouldExitMenu = true;
//  }

//pressedUp = digitalRead(8);
//pressedDown = digitalRead(6);
//pressedSelect = digitalRead(7);
//
//if( pressedUp == HIGH){    
//  do{
//    u8g2.drawStr(0,10,prompt);
//    u8g2.drawStr(0,20,"pressedUp");
//  } while ( u8g2.nextPage() );
//} else if( pressedDown == HIGH){    
//  do{
//    u8g2.drawStr(0,10,prompt);
//    u8g2.drawStr(0,20,"pressedDown");
//  } while ( u8g2.nextPage() );
//} else if( pressedSelect == HIGH){    
//  do{
//    u8g2.drawStr(0,10,prompt);
//    u8g2.drawStr(0,20,"pressedSelect");
//  } while ( u8g2.nextPage() );
//} else {
//    //u8g2.clear();
//    u8g2.drawStr(0,20,items[1]);
//}

  
    
    pressedUp = digitalRead(8);
    pressedDown = digitalRead(6);
    pressedSelect = digitalRead(7);
   
    if(pressedUp == HIGH) {
      if(selectedMenuItem > 0) {
            /* Passe au choix précédent */
            selectedMenuItem--;
            do{
              u8g2.drawStr(0,((selectedMenuItem+2)*10),">");
              u8g2.drawStr(10,((selectedMenuItem+2)*10),items[selectedMenuItem]);
            } while ( u8g2.nextPage() );
            
          }
          pressedButton = 0;
    } else if(pressedDown == HIGH){
      if(selectedMenuItem < (nbItems - 1)) {
            /* Passe au choix suivant */
            selectedMenuItem++;
            do{
              u8g2.drawStr(0,((selectedMenuItem+2)*10),">");
              u8g2.drawStr(10,((selectedMenuItem+2)*10),items[selectedMenuItem]);
            } while ( u8g2.nextPage() );
          }
          pressedButton = 0;
    } else if (pressedSelect == HIGH){
      callbackFnct(selectedMenuItem);
        pressedButton = 0;
    }
    
//    switch (pressedButton) {
//      case U8X8_MSG_GPIO_MENU_DOWN:
//          if(selectedMenuItem < (nbItems - 1)) {
//            /* Passe au choix suivant */
//            selectedMenuItem++;
//            u8g2.drawStr(0,((selectedMenuItem+1)*10),">");
//            u8g2.drawStr(10,((selectedMenuItem+1)*10),items[selectedMenuItem]);
//          }
//          pressedButton = 0;
//      break;
//      
//      case U8X8_MSG_GPIO_MENU_SELECT:
//        callbackFnct(selectedMenuItem);
//        pressedButton = 0;
//      break;
//      
//      case U8X8_MSG_GPIO_MENU_PREV:
//        shouldExitMenu = true;
//        pressedButton = 0;
//      break;
//      
//      case U8X8_MSG_GPIO_MENU_UP:
//          if(selectedMenuItem > 0) {
//            /* Passe au choix précédent */
//            selectedMenuItem--;
//            u8g2.drawStr(0,((selectedMenuItem+1)*10),">");
//            u8g2.drawStr(10,((selectedMenuItem+1)*10),items[selectedMenuItem]);
//          }
//          pressedButton = 0;
//      break;
//    }
}

//void checkButton(){
//
//  this.displayMenu();
//}
