#ifndef SCREENS_H
#define SCREENS_H

#define u8g_logo_width 32
#define u8g_logo_height 32

#include <Arduino.h>

//constantes de display des menus
/*
const int selectPin = 7;
const int upPin  = 8;
const int downPin = 6;
const int returnPin = 5;
const int ledPin = 9;
const int buzzerPin = 10;*/

const int nAge = 1;
const int nSubAge = 2;
const int nMonitoring = 3;
const int nSettings = 4;
const int nYesNo = 5;
const int nAlarm = 6;
const int nAlarmHelp = 7;

//constantes des menus
//const int nbWelcomeItems = 11;
const int nbWelcomeItems = 7;

const int nbAgeMenuItems = 11;
const int firstAge = 0;
const int lastAge = 10;
//const int prevAgeMenu = 3;

const int nbSubAgeItems = 10;
const int firstSubAge = 0;
const int lastSubAge = 9;
//const int prevSubAge = 1;

const int nbMonitoringItems = 10;
const int firstMonitoring = 8;
const int lastMonitoring = 9;
//const int prevMonitoring = 3;

const int nbSettingsItems = 11;
const int firstSettings = 5;
const int lastSettings = 6;
//const int prevSettings = 3;

const int nbYesNoItems = 11;
const int firstYesNo = 5;
const int lastYesNo = 6;
///const int prevYesNo = 4;

const int nbAlarmItems = 11;
const int firstAlarm = 10;
const int lastAlarm = 10;
//const int prevAlarm = 3;

const int nbAlarmHelpItems = 11;
const int firstAlarmHelp = 10;
const int lastAlarmHelp = 10;
//const int prevAlarmHelp = 3;

const int nbGoodbyeItems = 11;

static const char* NUMBERS[] = {
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "11"
};

static unsigned char u8g_logo1_bits[] = {
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
  //"      LOGO      ",
  //"      LOGO      ",
  //"",
  //"",
  "   Welcome to   ",
  "   Protech(t)   ",
  "",
  "",
  "   created by   ",
  "  Agathe Lievre ",
  "  Assia Nguyen  "
};

/* Selection de l'age */
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
 
/* Monitoring menu */
static const char* MONITORING_ITEMS[] = {
  "HeartRate:",
  "          .. BPM",
  "Temperature:",
  "               C",
  "Motion sensor:",
  "         no risk",
  "Age:",
  "BPM max:",
  "",
  " Call for help! ",
  "    Settings    "
};

/* Alarm without calling for help*/
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

/* Alarm calling for help*/
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

/* Settings */
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

/* Goodbye screen */
static const char* GOODBYE[] = {
  "",
  "",
  "",
  "",
  "  See you soon  ",
  "",
  "",
  "",
  "",
  "      LOGO      ",
  "      LOGO      "
};

#endif
