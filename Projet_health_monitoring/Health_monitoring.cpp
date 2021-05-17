#include "Health_monitoring.h"

//constantes de temps en microsecondes
#define DELAY_10_MIN 600000000
#define DELAY_15_SEC 15000000

//variables de suivi du déclenchement de l'alarme
unsigned long Monitoring::timeAlarm = 0;
unsigned long Monitoring::timeAlarmHelp = 0;
unsigned long Monitoring::timeFallen = 0;
bool Monitoring::alarmFallen = false;

//variables de suivi du menu actuel et du curseur
int Monitoring::actualMenu = nAge;
int Monitoring::cursorPosition = firstAge;

//variables des boutons
byte Monitoring::pressedUp = 0;
byte Monitoring::pressedDown = 0;
byte Monitoring::pressedSelect = 0;
byte Monitoring::pressedOnOff = 0;
int Monitoring::nonePressed = 1;

//varible this pour les fonctions statiques
Monitoring* Monitoring::This = 0;

//objets statiques pour les fonctions statiques
Led Monitoring::led = Led(false, ledPin); 
Buzzer Monitoring::buzzer = Buzzer(false, buzzerPin);
Oxymeter Monitoring::oxy = Oxymeter(false, false, 55.0, 200.0, oxyPin, 0.0);
Sms Monitoring::message = Sms(80);
Menu Monitoring::goodbye = Menu(GOODBYE, nbGoodbyeItems);
Menu Monitoring::blackScreen = Menu(BLACK_SCREEN, nbBlackScreenItems);

//constructeur vide
Monitoring::Monitoring(){
  upButton = Switch(false, upPin);
  selectButton = Switch(false, selectPin);
  downButton = Switch(false, downPin);
  onOffButton = Switch(false, onOffPin);
  temp = Temperature(false, false, 0.0, 38.0, 40.0, tempPin);
  accelero=Accelerometer(false, 0x18, 50);

  This = this;
  
  welcome = Menu(WELCOME, nbWelcomeItems);
  ageMenu = Menu("Select your age:", AGE_MENU_ITEMS, nbAgeMenuItems, firstAge, lastAge, &doAgeMenuAction);
  subAgeMenu = Menu("     Select:    ", SUB_AGE_ITEMS, nbSubAgeItems, firstSubAge, lastSubAge, &doSubAgeAction);
  monitoring = Menu("HealthMonitoring",MONITORING_ITEMS, nbMonitoringItems, firstMonitoring, lastMonitoring, &doMonitoringAction);
  settings = Menu("    Settings    ", SETTINGS_ITEMS, nbSettingsItems, firstSettings, lastSettings, &doSettingsAction);
  yesNo = Menu("   Turn off ?   ", YES_NO_ITEMS, nbYesNoItems, firstYesNo, lastYesNo, &doYesNoAction);
  alarm = Menu(" Alarm activated", ALARM_ITEMS, nbAlarmItems, firstAlarm, lastAlarm, &doAlarmAction);
  alarmHelp = Menu(" Alarm activated", ALARM_HELP_ITEMS, nbAlarmHelpItems, firstAlarmHelp, lastAlarmHelp, &doAlarmHelpAction);
}

//constructeur avec quelques attributs
Monitoring::Monitoring(Led lum,Buzzer buzz, Temperature thermo,Oxymeter oxym, Sms mess, Accelerometer accel){
  This = this;
  
  led = lum;
  buzzer = buzz;
  temp = thermo;
  oxy = oxym;
  message = mess;
  accel = accel;
}

//set up du monitor
void Monitoring::setUpMonitoring(){

  //set up des objets
  led.setUp(); 
  accelero.setUp();
  buzzer.setUp();
  upButton.setUp();
  downButton.setUp();
  selectButton.setUp();
  onOffButton.setUp();
  message.setUp();

  //affichage de l'écran d'accueil
  u8g2.begin();
  u8g2.setFont(u8g2_font_pressstart2p_8f);
  u8g2.firstPage();
  welcome.displayScreen(0);
  delay(2000);
  u8g2.clear();
}

//fait tourner le monitoring
void Monitoring::startMonitoring(){
  
  //récupère les valeurs des boutons
  pressedUp = upButton.getValue();
  pressedDown = downButton.getValue();
  pressedSelect = selectButton.getValue();
  pressedOnOff = onOffButton.getValue();

  //regarde quel bouton est appuyé
  //bouton rouge : bouton on/off
  if(pressedOnOff == HIGH){
    
    //si l'app est éteinte, il rallume l'app
    if(actualMenu == nBlackScreen){
      u8g2.begin();
      u8g2.setFont(u8g2_font_pressstart2p_8f);
      u8g2.firstPage();
      welcome.displayScreen(0);
      delay(2000);
      u8g2.clear();

      //retourne directement sur l'écran de monitoring
      actualMenu = nMonitoring;
      cursorPosition = this->getActualMenu().getFirst();
      nonePressed = 0;

    //si l'app est allumée, il demande à l'utilisateur s'il veut vraiment l'éteindre
    }else{

      //amène le menu de choix
      actualMenu = nYesNo;
      cursorPosition = this->getActualMenu().getFirst();
      nonePressed = 0;
    }

  //bouton vert : bouton pour selectionner
  }else if(pressedSelect == HIGH){

    //fait l'action du choix sélectionné
    this->getActualMenu().getCallbackFnct(cursorPosition);
    nonePressed = 0;

  //bouton bleu : bouton pour descendre
  }else if(pressedDown == HIGH){

    //si le curseur n'est pas sur le dernier choix, il descend
    if(cursorPosition<this->getActualMenu().getLast()){
      cursorPosition++;  
      nonePressed = 0;
    }

  //bouton jaune : bouton pour monter
  }else if(pressedUp == HIGH){

    //si le curseur n'est pas sur le premier choix, il monte
    if(cursorPosition>this->getActualMenu().getFirst()){
      cursorPosition--; 
      nonePressed = 0;   
    }

  //aucun bouton n'est appuyé
  }else{
    nonePressed = 1;
  }  

  //update les menus
  u8g2.firstPage();  

  //si on est sur le menu de monitoring
  if (actualMenu == nMonitoring){

    //on récupère les valeurs de température et d'accélération
    float temperature = temp.getValue();
    float acceleration = accelero.getValue();

    //on affiche ce menu
    this->getActualMenu().displayMenuM(cursorPosition, oxy.getAge(), oxy.getMaxValue(), temperature, acceleration);

    //on regarde si le patient est à risque
    temp.isAtRisk(temperature);
    accelero.isAtRisk(acceleration);

    //si le patient est tombé
    if(accelero.getAtRisk()){

      //on note l'heure de chute
      timeFallen = micros();

      //on va sur le menu d'alarme
      actualMenu = nAlarmHelp;
      cursorPosition = this->getActualMenu().getFirst();

      //on allume la LED et le buzzer
      led.turnOn();
      buzzer.turnOn();
      
      alarmFallen = true;
    }

    //si la température est inquiétante mais pas alarmante
    //et que c'est la première fois 
    //ou si l'alarme n'a pas sonné depuis plus de 1O min
    if((micros()>(timeAlarm+DELAY_10_MIN)) || (timeAlarm == 0)){
      if(temp.getWarning()){

        //on note l'heure de l'alerte
        timeAlarm = micros();

        //on va sur le menu d'alerte
        actualMenu = nAlarm;
        cursorPosition = this->getActualMenu().getFirst();

        //on allume la LED et le buzzer
        led.turnOn();
        buzzer.turnOn();
      }
    }

    //si la température est alarmante
    //et que c'est la première fois 
    //ou si l'alarme n'a pas sonné depuis plus de 1O min
    if((micros()>(timeAlarmHelp+DELAY_10_MIN)) || (timeAlarmHelp == 0)){
      if(temp.getAtRisk()){

        //on note l'heure de l'alarme
        timeAlarmHelp = micros();

        //on va sur le menu d'alarme
        actualMenu = nAlarmHelp;
        cursorPosition = this->getActualMenu().getFirst();

        //on envoie un message aux urgences et on allume la LED et le buzzer
        message.sendEvent("alarm_on");
        led.turnOn();
        buzzer.turnOn();
      }
    }

  //si l'app est éteinte
  }else if(actualMenu == nBlackScreen){

    //on affiche un écran noir
    this->getActualMenu().displayScreen(2);

  //si on est sur n'importe quel autre menu 
  }else{

    //on affiche le menu
    this->getActualMenu().displayMenu(cursorPosition);

    //si on est sur le menu d'alarme après une chute et qu'on ne l'a pas désactivé après 15 secondes
    //on envoie un message aux urgences
    if((micros()>timeFallen+DELAY_15_SEC) && (actualMenu == nAlarmHelp) && (alarmFallen)){
      message.sendEvent("alarm_on");
      alarmFallen = false;
    }
  } 
}

//return le menu correspondant au numéro de menu
Menu Monitoring::getActualMenu(){
  switch(actualMenu){
      case 1:
        return ageMenu;
      break;
      case 2:
        return subAgeMenu;
      break;
      case 3:
        return monitoring;
      break;
      case 4:
        return settings;
      break;
      case 5:
        return yesNo;
      break;
      case 6:
        return alarm;
      break;
      case 7:
        return alarmHelp;
      break;
      case 8:
        return blackScreen;
      break;
  }
}

//fait les actions des choix du menu de sélection du chiffre des dizaines de l'âge
void Monitoring::doAgeMenuAction(int selectedMenuItem){

  //pour chaque choix, sélectionne le chiffre des dizaines de l'âge
  //et va sur le menu de sélection du chiffre des unités de l'âge
  switch(selectedMenuItem){
    
    case 0:
    oxy.setAgeDiz(1);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
    case 1:
    oxy.setAgeDiz(2);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
    case 2:
    oxy.setAgeDiz(3);
    u8g2.clear();
    actualMenu = nSubAge;    
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 3:
    oxy.setAgeDiz(4);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 4:
    oxy.setAgeDiz(5);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 5:
    oxy.setAgeDiz(6);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 6:
    oxy.setAgeDiz(7);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 7:
    oxy.setAgeDiz(8);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 8:
    oxy.setAgeDiz(9);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 9:
    oxy.setAgeDiz(10);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 10:
    oxy.setAgeDiz(11);
    u8g2.clear();
    actualMenu = nSubAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

//fait les actions des choix du menu de sélection du chiffre des unités de l'âge
void Monitoring::doSubAgeAction(int selectedMenuItem){

  //pour chaque choix, sélectionne le chiffre des unités de l'âge,
  //calcule l'âge et va sur le menu de monitoring
  switch(selectedMenuItem){
    
    case 0:
    oxy.setAgeUnit(0);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
    case 1:
    oxy.setAgeUnit(1);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
 
    case 2:
    oxy.setAgeUnit(2);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 3:
    oxy.setAgeUnit(3);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 4:
    oxy.setAgeUnit(4);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 5:
    oxy.setAgeUnit(5);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 6:
    oxy.setAgeUnit(6);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 7:
    oxy.setAgeUnit(7);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    case 8:
    oxy.setAgeUnit(8);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
    
    case 9:
    oxy.setAgeUnit(9);
    oxy.calculateAge();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}
 
//fait les actions des choix du menu de monitoring
void Monitoring::doMonitoringAction(int selectedMenuItem){
  
  switch(selectedMenuItem){

    //allume l'alarme, envoie un message aux urgences et va sur le menu de l'alarme
    case 8:
    message.sendEvent("alarm_on");
    led.turnOn();
    buzzer.turnOn();
    u8g2.clear();
    actualMenu = nAlarmHelp;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    //va sur le menu des settings
    case 9:
    u8g2.clear();
    actualMenu = nSettings;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

//fait les actions des choix du menu de settings
void Monitoring::doSettingsAction(int selectedMenuItem){
  
  switch(selectedMenuItem){
    
    //va sur le menu du choix de l'âge
    case 5:
    u8g2.clear();
    actualMenu = nAge;
    cursorPosition = This->getActualMenu().getFirst();
    break;

    //retourne sur le menu de monitoring
    case 6:
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

//fait les actions des choix du menu de de choix (yes or no)
void Monitoring::doYesNoAction(int selectedMenuItem){
  
  switch(selectedMenuItem){

    //affiche l'écran de fermeture
    //et éteint l'app
    case 5:
    u8g2.firstPage();
    goodbye.displayScreen(1);
    delay(2000);
    actualMenu = nBlackScreen;
    break;

    //retourne sur le menu du monitoring
    case 6:
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

//fait les actions des choix du menu d'alerte
void Monitoring::doAlarmAction(int selectedMenuItem){
  
  switch(selectedMenuItem){

    //éteint l'alerte et retourne sur le menu de monitoring
    case 10:
    led.turnOff();
    buzzer.turnOff();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}

//fait les actions des choix du menu d'alarme
void Monitoring::doAlarmHelpAction(int selectedMenuItem){
  
  switch(selectedMenuItem){

    //éteint l'alarme et retourne sur le menu de monitoring
    case 10:
    led.turnOff();
    buzzer.turnOff();
    u8g2.clear();
    actualMenu = nMonitoring;
    cursorPosition = This->getActualMenu().getFirst();
    break;
  }
}
