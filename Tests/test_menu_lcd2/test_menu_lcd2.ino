/* Inclut la librairie LiquidCrystal pour le LCD */
#include <LiquidCrystal.h>
#include "Menu.h" // Fichier d'entête avec les types pour le menu
 
/* Objet LCD sur les broches utilisées par la shield LCD DFrobots */
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte buttons[] = {6,7,8}; //10 for additional pin
const byte nrButtons = 3; // change to 4 if additional button added

int t;
byte pressedButton;

/* Menu principal */
static const char* MAIN_MENU_ITEMS[] = {
  "John Doe",
  "Skywodd",
  "Dr Freeman",
  "Nyan Cat",
  "Obiwan Kenobi"
};

/* Sous menu pour Dr Freeman */
static const char* FREEMAN_MENU_ITEMS[] = {
  "Gordon Freeman",
  "Morgan Freeman",
  "Martin Freeman"
};

 /** Affiche le choix de l'utilisateur */
void doFreemanMenuAction(byte selectedMenuItem) {
 
  /* Affiche le choix de l'utilisateur */
  displayChoice(selectedMenuItem, FREEMAN_MENU_ITEMS);
}

static const Menu_t FREEMAN_MENU = {
  "Votre choix ?",
  FREEMAN_MENU_ITEMS,
  3,
  &doFreemanMenuAction
};

/** Affiche le choix de l'utilisateur */
void doMainMenuAction(byte selectedMenuItem) {
 
  /* Cas spécial pour Dr Freeman */
  if(selectedMenuItem == 2) {
 
    /* Affiche le sous-menu pour Dr Freeman */
    displayMenu(FREEMAN_MENU);
 
  } else {
 
    /* Affiche le choix de l'utilisateur */
    displayChoice(selectedMenuItem, MAIN_MENU_ITEMS);
  }
}

static const Menu_t MAIN_MENU = {
  "Votre choix ?",
  MAIN_MENU_ITEMS,
  5,
  &doMainMenuAction
};
 
/** Setup */
void setup() {
 
  /* Configuration du LCD */
  lcd.begin(16, 2);
}
 
/** Programme principal */
void loop() {
 
  /* Affiche le menu principal */
  displayMenu(MAIN_MENU);

}
 
// Look for a button press
byte checkButtonPress() {
  byte bP = 0;
  byte rBp = 0;
  for (t = 0; t<nrButtons;t++) {
    if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
  }
  rBp = bP;
  while (bP != 0) { // wait while the button is still down
    bP = 0;
    for (t = 0; t<nrButtons;t++) {
      if (digitalRead(buttons[t]) == 0) {bP = (t + 1);}
    }
  }
  return rBp;
}

/** Fonction retournant le bouton appuyé (s’il y en a un). */
Button_t readPushButton(void) {
   pressedButton = checkButtonPress();

  if (pressedButton !=0) {
    switch (pressedButton) {
      case 1:
          return BP_LEFT; //RETURN
      break;
      case 2:
        return BP_RIGHT; //SELECT
      break;
      case 3:
       return BP_DOWN; //SCROLL DOWN
      break;
      case 4:
        return BP_UP; //SCROLL UP
      break;
    }
  } else {
    return BP_NONE; 
  }
}
 
/** Affiche le menu passé en argument */
void displayMenu(const Menu_t &menu) {
 
  /* Variable pour le menu */
  byte selectedMenuItem = 0;   // Choix selectionné
  byte shouldExitMenu = false; // Devient true quand l'utilisateur veut quitter le menu
  Button_t buttonPressed;      // Contient le bouton appuyé
 
  /* Tant que l'utilisateur ne veut pas quitter pas le menu */
  while(!shouldExitMenu) {
 
    /* Affiche le menu */
    lcd.clear();
    lcd.print(menu.prompt);
    lcd.setCursor(0, 1);
    lcd.print(menu.items[selectedMenuItem]);
 
    /* Attend le relâchement du bouton */
    while(readPushButton() != BP_NONE);
 
    /* Attend l'appui sur un bouton */
    while((buttonPressed = readPushButton()) == BP_NONE);
 
    /* Anti rebond pour le bouton */
    delay(30);
 
    /* Attend le relâchement du bouton */
    while(readPushButton() != BP_NONE);
 
    /* Gére l'appui sur le bouton */
    switch(buttonPressed) {
    case BP_UP: // Bouton haut = choix précédent
 
      /* Si il existe un choix précédent */
      if(selectedMenuItem > 0) {
 
        /* Passe au choix précédent */
        selectedMenuItem--;
      }
      break;
 
    case BP_DOWN: // Bouton bas = choix suivant
 
      /* Si il existe un choix suivant */
      if(selectedMenuItem < (menu.nbItems - 1)) {
 
        /* Passe au choix suivant */
        selectedMenuItem++;
      }
      break;
 
    case BP_LEFT: // Bouton gauche = sorti du menu
      shouldExitMenu = true;
      break;
 
    case BP_SELECT: //
    case BP_RIGHT:  // Bouton droit ou SELECT = validation du choix
      menu.callbackFnct(selectedMenuItem);
      break;
    }
  }
}
 
/** Affiche le choix de l'utilisateur */
void displayChoice(byte selectedMenuItem, const char** items) {
 
  /* Affiche le choix de l'utilisateur */
  lcd.clear();
  lcd.print(F("Z'avez choisi :"));
  lcd.setCursor(0, 1);
  lcd.print(items[selectedMenuItem]);
 
  /* Attend l'appui sur le bouton gauche ou SELECT */
  byte buttonPressed;
  do {
    buttonPressed = readPushButton();
  } 
  while(buttonPressed != BP_LEFT && buttonPressed != BP_SELECT);
}
