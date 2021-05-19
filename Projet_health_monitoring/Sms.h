#ifndef SMS_H
#define SMS_H

#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

// paramètres pour se connecter au Wifi + url
//à modifier selon le Wifi utilisé

//nom du modem
static const char* ssid = "Livebox-6150";

//mot de passe
static const char* pass = "Knw66jzLxL4dkcEEzL";

//site pour l'envoie du message
static const char *host = "maker.ifttt.com";

//clé privée de l'évènement
static const char *privateKey = "KyzwOybgYJBeVvQQD_1IX";

class Sms {
  
  friend class Monitoring;
  
  protected:

    int httpPort;

  public :

    //constructeurs
    Sms();
    Sms(int port);

    //méthodes
    void setUp();
    void sendEvent(const char *event);
};

#endif
