#include "ESP8266WiFi.h"

const char* ssid = "LAPTOP-LC2431QO7163"; //Enter SSID
const char* password = "c6630D88"; //Enter Password

void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin("LAPTOP-LC2431QO7163", "c6630D88");
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() 
{
  // EMPTY
}
