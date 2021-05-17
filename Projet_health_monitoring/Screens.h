#ifndef SCREENS_H
#define SCREENS_H

//hauteur et largeur du logo
#define u8g_logo_width 32
#define u8g_logo_height 32

#include <Arduino.h>

//numéro des pins des objets
const int ledPin = D8;
const int buzzerPin = D2;
const int oxyPin = A0;
const int upPin  = D12;
const int selectPin = D11;
const int downPin = D10;
const int onOffPin = D6;
const int tempPin  = A0;

//numéro des menus
const int nAge = 1;
const int nSubAge = 2;
const int nMonitoring = 3;
const int nSettings = 4;
const int nYesNo = 5;
const int nAlarm = 6;
const int nAlarmHelp = 7;
const int nBlackScreen = 8;

//constantes des menus
//welcome menu
const int nbWelcomeItems = 7;

//age menu
const int nbAgeMenuItems = 11;
const int firstAge = 0;
const int lastAge = 10;

//sub age menu
const int nbSubAgeItems = 10;
const int firstSubAge = 0;
const int lastSubAge = 9;

//monitoring menu
const int nbMonitoringItems = 11;
const int firstMonitoring = 8;
const int lastMonitoring = 9;

//settings menu
const int nbSettingsItems = 11;
const int firstSettings = 5;
const int lastSettings = 6;

//yes or no menu
const int nbYesNoItems = 11;
const int firstYesNo = 5;
const int lastYesNo = 6;

//alerte menu
const int nbAlarmItems = 11;
const int firstAlarm = 10;
const int lastAlarm = 10;

//alarm menu
const int nbAlarmHelpItems = 11;
const int firstAlarmHelp = 10;
const int lastAlarmHelp = 10;

//goodbye menu
const int nbGoodbyeItems = 6;

//black screen
const int nbBlackScreenItems = 0;

//tableau du logo
static unsigned char u8g_logo_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x18, 0x00, 
  0x00, 0x00, 0x18, 0x00, 0x00, 0x3C, 0x06, 0x00, 0x80, 0x7E, 0x17, 0x00, 
  0x80, 0xFF, 0x5B, 0x00, 0x40, 0xFF, 0xDB, 0x00, 0xC0, 0xFE, 0xDB, 0x00, 
  0xC0, 0xFE, 0xDB, 0x0F, 0xA0, 0xFE, 0xDD, 0x01, 0x38, 0x0E, 0x5C, 0x01, 
  0x00, 0xF4, 0x9F, 0x00, 0x00, 0xF8, 0xBF, 0x00, 0x00, 0xF8, 0xAF, 0x00, 
  0x00, 0xF0, 0xC7, 0x00, 0x00, 0xE0, 0xC3, 0x00, 0x00, 0xC0, 0x41, 0x00, 
  0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

//Welcome screen
static const char* WELCOME[] = {
  "   Welcome to   ",
  "   Protech(t)   ",
  "",
  "",
  "   created by   ",
  "  Agathe Lievre ",
  "  Assia Nguyen  "
};

//age screen
static const char* AGE_MENU_ITEMS[] = {
  "    10 - 19     ",
  "    20 - 29     ",
  "    30 - 39     ",
  "    40 - 49     ",
  "    50 - 59     ",
  "    60 - 69     ",
  "    70 - 79     ",
  "    80 - 89     ",
  "    90 - 99     ",
  "   100 - 109    ",
  "   110 - 119    "
};

//sub age screen
static const char* SUB_AGE_ITEMS[] = {
  "       -0       ",
  "       -1       ",
  "       -2       ",
  "       -3       ",
  "       -4       ",
  "       -5       ",
  "       -6       ",
  "       -7       ",
  "       -8       ",
  "       -9       "
};
 
//monitoring screen
static const char* MONITORING_ITEMS[] = {
  "HeartRate:",
  "          .. BPM",
  "Temperature:",
  "               C",
  "Motion sensor:",
  "",
  "Age:",
  "BPM max:",
  "",
  " Call for help! ",
  "    Settings    "
};

//alert screen
static const char* ALARM_ITEMS[] = {
  "",
  "",
  " Risk of health ",
  "   problems!",
  "",
  "",
  " Please consult ",
  "  your doctor!  ",
  "",
  "",
  "Deactivate alarm"
};

//alarm screen
static const char* ALARM_HELP_ITEMS[] = {
  "",
  "",
  "   Calling for  ",
  "     help...    ",
  "",
  "",
  "Patient at great",
  "      risk      ",
  "",
  "",
  "Deactivate alarm"
};

//settings screen
static const char* SETTINGS_ITEMS[] = {
  "",
  "",
  "",
  "",
  "",
  "   Change age   ",
  "  Exit settings ",
  "",
  "",
  "",
  ""
};

//yes or no screen
static const char* YES_NO_ITEMS[] = {
  "",
  "",
  "",
  "",
  "",
  "      Yes!      ",
  "       No       ",
  "",
  "",
  "",
  ""
};

//goodbye screen
static const char* GOODBYE[] = {
  "    Goodbye!    ",
  "",
  "",
  "",
  "",
  "  See you soon  "
};

//black screen
static const char* BLACK_SCREEN[] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""
};

#endif
