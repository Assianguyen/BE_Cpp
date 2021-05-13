#include <Wire.h>
#include <ESP8266WiFi.h>

// WiFi network info.
//const char *ssid =  "ViewLiteAssia";     // Enter your WiFi Name
//const char *pass =  "3399fc7ac862"; // Enter your WiFi Password

//const char *ssid =  "Gathou";     // Enter your WiFi Name
//const char *pass =  "12345678"; // Enter your WiFi Password

boolean fall=true;
const char* ssid = "Livebox-43BA";
const char* pass = "mxsxmTxN32ZGeeRpjo";

void send_event(const char *event);
const char *host = "maker.ifttt.com";
const char *privateKey = "KyzwOybgYJBeVvQQD_1IX";
void setup(){
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
 }
void loop(){
 
 if (fall==true){ //in event of a fall detection
   Serial.println("FALL DETECTED");
   send_event("alarm_on"); 
   fall=false;
   }

  delay(100);
  }

void send_event(const char *event)
{
  Serial.print("Connecting to "); 
  Serial.println(host);
    // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
    // We now create a URI for the request
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      // No data yet, wait a bit
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}
