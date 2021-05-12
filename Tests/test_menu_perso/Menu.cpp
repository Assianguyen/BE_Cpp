#include "Menu.h"

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
