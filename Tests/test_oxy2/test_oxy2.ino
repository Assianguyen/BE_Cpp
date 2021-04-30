void setup() {
  Serial.begin(9600);
}

void loop() {
  //int sensorValue = analogRead(A0);
  Serial.print("BPM = ");
  Serial.println(analogRead(A0));
  delay(100);
}
