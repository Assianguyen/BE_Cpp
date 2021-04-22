#define touchPin D1 // Pin for capactitive touch sensor
 
void setup() 
{
  Serial.begin(9600); 
  pinMode(touchPin, INPUT);
}
 
void loop() 
{
  int touchValue = digitalRead(touchPin);
  if (touchValue == HIGH)
  {
    Serial.println("TOUCHED");
  }
  else
  {
    Serial.println("not touched");
  } 
  delay(500);
 
}
