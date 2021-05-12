#ifndef SMS_H
#define SMS_H

#include <Arduino.h>




// paramètres pour se connecter au Wifi + url
 static const char* ssid = "Livebox-6150";
 static const char* pass = "Knw66jzLxL4dkcEEzL";
 static const char *host = "maker.ifttt.com";
 static const char *privateKey = "KyzwOybgYJBeVvQQD_1IX";


class Sms {
friend class Monitoring;
  
protected:

  int httpPort;

public :

 Sms();
 Sms(int port);
 void setUp();
 void sendEvent(const char *event);
 

};
#endif
