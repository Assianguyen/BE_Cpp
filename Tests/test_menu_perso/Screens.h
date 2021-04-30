#ifndef SCREENS_H
#define SCREENS_H

#include <Arduino.h>
using namespace std;

static const int nbWelcomeItems = 11;
static const int nbAgeMenuItems = 10;
static const int nbSubAgeItems = 10;
static const int nbMonitoringItems = 10;
static const int nbSettingsItems = 11;
static const int nbYesNoItems = 11;
static const int nbGoodbyeItems = 11;
static const int nbAlarmItems = 11;
static const int nbAlarmHelpItems = 11;


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
  "",
  "    20 - 29     ",
  "    30 - 39     ",
  "    40 - 49     ",
  "    50 - 59     ",
  "    60 - 69     ",
  "    70 - 79     ",
  "    80 - 89     ",
  "    90 - 99     ",
  "   100 - 109    ",
  ""
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
  "",
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
  "",
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
  "See you soon",
  "",
  "",
  "",
  "",
  "LOGO",
  "LOGO"
};

#endif
