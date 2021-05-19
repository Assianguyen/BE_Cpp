#include "Menu.h"

//définition de l'écran OLED
extern U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

//constructeur vide
Menu::Menu(){
  items = 0;
  nbItems = 0;
}

//constructeur avec comme arguments les choix
Menu::Menu(const char** choix, int nbChoix){
  items = choix;
  nbItems = nbChoix;
}

//constructeur avec tous les arguments
Menu::Menu(const char* nom, const char** choix, int nbChoix, int first, int last, void (*function)(int selection)){

  //exceptions
  if((nbChoix < last) || (first > last)){
    throw std::invalid_argument("Mauvais arguments : nbItems, firstChoice ou lastChoice");
  }else{
    prompt = nom;
    items = choix;
    nbItems = nbChoix;
    firstChoice = first;
    lastChoice = last;
    callbackFnct = function;
  }
}

//getters
const char* Menu::getPrompt(){
  return prompt;
}

const char* Menu::getSelectedItem(int selectedItem){
  return items[selectedItem];
}

const char** Menu::getItems(){
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

//affiche les écrans de bienvenue (0), de fermeture (1), noir (2)
void Menu::displayScreen(int nMenu){

  //affiche l'écran de bienvenue avec le logo
  if(nMenu == 0){
    do{
      
      //logo
      u8g2.setDrawColor(1);
      u8g2.drawXBM( 50, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);

      //menu
      u8g2.setDrawColor(2);
      for (int i = 0; i < nbItems; i++){
        u8g2.drawStr(0,((i + 5) * 10), items[i]);
      }
    }while (u8g2.nextPage());

  //affiche l'écran de fermeture avec le logo
  }else if(nMenu == 1){
    do{

      //logo
      u8g2.setDrawColor(1);
      u8g2.drawXBM( 50, 90, u8g_logo_width, u8g_logo_height, u8g_logo_bits);

      //menu
      u8g2.setDrawColor(2);
      for (int i = 0; i < nbItems; i++){
        u8g2.drawStr(0,((i + 1) * 10), items[i]);
      }
    }while (u8g2.nextPage());

  //affiche l'écran noir
  }else if(nMenu == 2){
    do{
      u8g2.setDrawColor(2);
      for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i + 1) * 10), items[i]);
      }
    }while (u8g2.nextPage());
  }  
}

//affiche un menu
void Menu::displayMenu(int cursorP){

  //affiche le menu et surligne la position du curseur
  do{

    //curseur
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, ((cursorP + 1) * 10) + 1, 140, 10);

    //titre
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.setDrawColor(2);
    u8g2.drawStr(0, 10, prompt);

    //menu
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i + 2) * 10), items[i]);
    }
  }while (u8g2.nextPage());
}

//affiche le menu de monitoring
void Menu::displayMenuM(int cursorP, int age, int maxBpm, float temp, float accelero) {

  //affiche le menu de monitoring et surligne la position du curseur
  do{

    //curseur
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, ((cursorP + 1) * 10) + 1, 140, 10);

    //age
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.setDrawColor(2);
    u8g2.setCursor(40, 70);
    u8g2.print(age);

    //max bpm
    u8g2.setCursor(70, 80);
    u8g2.print(maxBpm);

    //température
    u8g2.setCursor(70, 40);
    u8g2.print(temp);
    u8g2.drawGlyph(110, 40, 0x00ba);

    //accéléromètre
    u8g2.setCursor(70, 60);
    u8g2.print(accelero);

    //menu
    for (int i = 0; i < nbItems; i++){
      u8g2.drawStr(0,((i + 1) * 10), items[i]);
    }    
  }while (u8g2.nextPage());
}

//surchage de l'opérateur []
const char* &Menu::operator[](int index){
  if(index > nbItems){
    //exception
    throw std::out_of_range("L'index est plus grand que la taille du tableau");
    //return items[0];
  }else{
    return items[index];
  }
}
