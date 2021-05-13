#include "Menu.h"
#include "Screens.h"
#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

//constructeurs
Menu::Menu()
{
  items = 0;
  nbItems = 0;
}

Menu::Menu(const char** choix, int nbChoix)
{
  items = choix;
  nbItems = nbChoix;
}

Menu::Menu(const char* nom, const char** choix, int nbChoix, int first, int last, void (*function)(int selection))
{
	prompt = nom;
  items = choix;
  nbItems = nbChoix;
  firstChoice = first;
  lastChoice = last;
  callbackFnct = function;
}

//méthodes
void Menu::setUp(){
  this->displayScreen();
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

void Menu::getCallbackFnct(int selectedItem){
  callbackFnct(selectedItem);
}

void Menu::displayScreen() {
  do {
    //u8g2.drawXBM( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo1_bits);
    for (int i = 0; i < nbItems; i++){
      u8g2.setDrawColor(2);
      u8g2.drawStr(0,((i+5)*10),items[i]);
    }
  } while ( u8g2.nextPage() );
}

void Menu::displayMenu(int cursorP) {
   do {
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, ((cursorP+1)*10)+1, 140, 10);
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.setDrawColor(2);
    u8g2.drawStr(0,10,prompt);
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+2)*10),items[i]);
    }
    } while ( u8g2.nextPage() );
}

void Menu::displayMenuM(int cursorP, int ageD, int ageU) {
   //const char *num[] =  {"0","1","2","3","4","5","6","7","8","9"};
   const char** n = NUMBERS;
   do {
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, ((cursorP+1)*10)+1, 140, 10);
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.setDrawColor(2);
    u8g2.drawStr(0,10,prompt);
    u8g2.drawStr(60,80, n[ageD]);
    u8g2.drawStr(70,80,n[ageU]);
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i+2)*10),items[i]);
    }    
    } while ( u8g2.nextPage() );
}
