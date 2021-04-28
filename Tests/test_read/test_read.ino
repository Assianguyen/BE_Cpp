void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  int intlu = 0;

  int dispo = 0;
  
  dispo = Serial.available();
  while(dispo> 0){  
    Serial.println("quel est ton age ?");
    intlu = Serial.read();
    Serial.print("age : ");
    Serial.println(intlu);
    dispo = Serial.available();
  }
}
