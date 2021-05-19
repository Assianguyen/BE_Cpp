#include "Sms.h"

//constructeur vide
Sms::Sms(){
  httpPort = 0;
}

//constructeur avec attributs
Sms::Sms(int port){
  httpPort = port;  
}

//set up des messages
void Sms::setUp(){

  //connexion au Wifi
  Wire.begin();
  WiFi.begin(ssid, pass);

  //vérification de la connexion
  //sortie du while quand la connexion est établie
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

//envoie du SMS
void Sms::sendEvent(const char *event){
  
  //Utilisation de la classe WiFiClient pour créer une connexion TCP
  WiFiClient client;

  //si la connexion a échoué, on arrête
  if (!client.connect(host, httpPort)){
    return;
  }
  
  //création d'un URL pour la requête
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;
  
  //envoie de la requête au serveur
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  //attente de la connexion
  while(client.connected()){
    if(client.available()){
      String line = client.readStringUntil('\r');
    } else {
      
      //attente de data
      delay(50);
    };
  }
  
  //fermeture de la connexion
  client.stop();
}
