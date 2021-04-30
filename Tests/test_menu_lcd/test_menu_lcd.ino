#include <LiquidCrystal.h>
#include "Functions.h"
#include "Pitches.h"
#include "Symbols.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte buttons[] = {6,7,8}; //10 for additional pin
const byte nrButtons = 3; // change to 4 if additional button added

int menusize = 11;

String menu[] = {
  "Menu",                   //0
  "Menu>LED",               //1
  "Menu>LED>Off",           //2
  "Menu>LED>On",            //3
  "Menu>LED>Fade",          //4
  "Menu>LED>Blink",         //5
  "Menu>LCDlight",          //6
  "Menu>Buzzer",            //7  
  "Menu>Buzzer>Off",        //8
  "Menu>Buzzer>On",         //9
  "Menu>Buzzer>Alarm"       //10
};

int t;
byte pressedButton, currentPos,currentPosParent, possiblePos[20], possiblePosCount, possiblePosScroll = 0;
String parent = "";

int brightness;
int LCDtoggle = 0;
int fadeAmount = 5;
unsigned long timer = (millis() / 10);
int ledMode = 0;
int buzzerMode = 0;
int ledPort = 9;
int buzzerPort = 10;
int lcdPort = 13;

void updateMenu () {
  possiblePosCount = 0;
  while (possiblePosCount == 0) {
    
    for (t = 1; t < menusize;t++) {
      if (mid(menu[t],1,inStrRev(menu[t],">")-1).equals(menu[currentPos])) {
        possiblePos[possiblePosCount]  =  t;
        possiblePosCount = possiblePosCount + 1;
      }
    }
    
    //find the current parent for the current menu
    parent = mid(menu[currentPos],1,inStrRev(menu[currentPos],">")-1);
    currentPosParent = 0;
    for (t = 0; t < menusize; t++) {
       if (parent == menu[t]) {currentPosParent = t;}
    }

    // reached the end of the Menu line
    if (possiblePosCount == 0) {
      //Menu Option Items
      switch (currentPos) {
        case 2:
        case 3:
        case 4:
        case 5://Choose between 2,3,4,5
          for (t = 2; t<6; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
        break;
        case 6: //Toggle
          if (mid(menu[currentPos],len(menu[currentPos]),1) == "*") {
            menu[currentPos] = mid(menu[currentPos],1,len(menu[currentPos])-1);
          } else {
            menu[currentPos] = menu[currentPos] + "*";    
          }
        break;
        case 8:
        case 9:
        case 10://Choose between 8,9,10
          for (t = 8; t<11; t++) {
            if (mid(menu[t],len(menu[t]),1) == "*") {
              menu[t] = mid(menu[t],1,len(menu[t])-1);
            }
          }
          menu[currentPos] = menu[currentPos] + "*";
        break;
      }

      //Set Variables
      switch (currentPos) {
        case 2:
          ledMode = 0;
        break;
        case 3:
          ledMode = 1;
        break;
        case 4:
          brightness = 128;
          ledMode = 2;
        break;
        case 5:
          brightness = 0;
          ledMode = 3;
        break;
        case 6:
          LCDtoggle = abs(LCDtoggle - 1);
          digitalWrite(lcdPort,LCDtoggle);
        break;
        case 8:
          buzzerMode = 0;
        break;
        case 9:
          buzzerMode = 1;
        break;
        case 10:
          buzzerMode = 2;
        break;
      }


      // go to the parent
      currentPos = currentPosParent;
    }
  }
    lcd.clear();
    switch (currentPos) {
        case 1:
          lcd.setCursor(0, 0);
          lcd.write(byte(2));
        break;
        case 7:
          lcd.setCursor(0, 0);
          lcd.write(byte(4));
        break;
      }
    lcd.setCursor(2,0); 
    lcd.print(mid(menu[currentPos],inStrRev(menu[currentPos],">")+1,len(menu[currentPos])-inStrRev(menu[currentPos],">")));
    lcd.setCursor(2,1); 
    lcd.print(mid(menu[possiblePos[possiblePosScroll]],inStrRev(menu[possiblePos[possiblePosScroll]],">")+1,len(menu[possiblePos[possiblePosScroll]])-inStrRev(menu[possiblePos[possiblePosScroll]],">")));
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

void setup() {
  
  lcd.begin(16,2); 
  // Create a new characters:
  lcd.createChar(0, Heart);
  lcd.createChar(1, Bell);
  lcd.createChar(2, Light);
  lcd.createChar(3, Check);
  lcd.createChar(4, Speaker);
  lcd.createChar(5, Sound);
  lcd.createChar(6, Skull);
  lcd.createChar(7, Lock);
  // Clears the LCD screen:
  lcd.clear();
  
  for (t=0;t<nrButtons;t++) {
    pinMode(buttons[t],INPUT_PULLUP); 
  }
  
  pinMode(lcdPort,OUTPUT);
  pinMode(ledPort,OUTPUT);
  pinMode(buzzerPort,OUTPUT);

  lcd.setCursor(0,0); 
  lcd.print("HELLO");
  delay(1000);
  updateMenu();

}

void loop() {

  
  switch (ledMode) {
    case 0:
      analogWrite(ledPort, 0);
    break;
    case 1:
      analogWrite(ledPort, 255);
    break;
    case 3:
      if ((millis() / 10) - timer > 30) {
        timer = (millis() / 10);
        brightness = abs(brightness - 255);
        timer = (millis() / 10);
        analogWrite(ledPort, brightness);
      }
    break;
    case 2:
      if ((millis() / 10) - timer > 3) {
        timer = (millis() / 10);
        analogWrite(ledPort, brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
        }
      }
    break;
  }

  switch (buzzerMode) {
    case 0:
      digitalWrite(buzzerPort, LOW);
    break;
    case 1:
      digitalWrite (buzzerPort, HIGH);
    break;
    case 2:
      digitalWrite (buzzerPort, HIGH);
    break;
  }

  pressedButton = checkButtonPress();
  if (pressedButton !=0) {
    switch (pressedButton) {
      case 1:
          possiblePosScroll = (possiblePosScroll + 1) % possiblePosCount; // Scroll
      break;
      // If I wanted a 4 button controll of the menu
      //case 4:
        //  possiblePosScroll = (possiblePosScroll + possiblePosCount - 1) % possiblePosCount; // Scroll
      //break;
      case 2:
        currentPos = possiblePos[possiblePosScroll]; //Okay
      break;
      case 3:
        currentPos = currentPosParent; //Back
        possiblePosScroll = 0;
      break;
    }
    updateMenu();
  }
}
