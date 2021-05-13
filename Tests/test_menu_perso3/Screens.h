#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
using namespace std;

const int nbWelcomeItems = 11;

const int nbAgeMenuItems = 11;
const int firstAge = 0;
const int lastAge = 10;
const int prevAgeMenu = 3;

const int nbSubAgeItems = 10;
const int firstSubAge = 0;
const int lastSubAge = 9;
const int prevSubAge = 1;

const int nbMonitoringItems = 10;
const int firstMonitoring = 7;
const int lastMonitoring = 9;
const int prevMonitoring = 3;

const int nbSettingsItems = 11;
const int firstSettings = 5;
const int lastSettings = 6;
const int prevSettings = 3;

const int nbYesNoItems = 11;
const int firstYesNo = 5;
const int lastYesNo = 6;
const int prevYesNo = 4;

const int nbAlarmItems = 11;
const int firstAlarm = 10;
const int lastAlarm = 10;
const int prevAlarm = 3;

const int nbAlarmHelpItems = 11;
const int firstAlarmHelp = 10;
const int lastAlarmHelp = 10;
const int prevAlarmHelp = 3;

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
  "9"
};

//Welcome screen
static const char* WELCOME[] = {
  "      LOGO      ",
  "      LOGO      ",
  "",
  "",
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
  "        .. degC",
  "Motion sensor:",
  "         no risk",
  "Age :",
  " Call for help! ",
  "    Settings    ",
  "    Turn off    "
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

/* Choice menu */
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
