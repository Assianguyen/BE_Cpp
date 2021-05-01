#include "Menu.h"
#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

Menu::Menu(const char* nom, const char** choix, int nbChoix)
{
  prompt = nom;
  items = choix;
  nbItems = nbChoix;
  //callbackFnct = null;
}

Menu::Menu(const char* nom, const char** choix, int nbChoix,int first, int last, int prev, void (*function)(int selection))
{
	prompt = nom;
  items = choix;
  nbItems = nbChoix;
  firstChoice = first;
  lastChoice = last;
  prevMenu = prev;
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

int Menu::getNbItems(){
  return nbItems;
}

int Menu::getLast(){
  return lastChoice;
}

int Menu::getFirst(){
  return firstChoice;
}

int Menu::getPrev(){
  return prevMenu;
}

void Menu::getCallbackFnct(int selectedItem){
  callbackFnct(selectedItem);
}

void Menu::displayScreen() {
  do {
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+1)*10),items[i]);
    }
  } while ( u8g2.nextPage() );
}

void Menu::displayMenu() {
   do {
    u8g2.drawStr(0,10,prompt);
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+2)*10),items[i]);
    }
   } while ( u8g2.nextPage() );
}
