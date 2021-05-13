//int led = D3;

void setup() {
  pinMode(9, OUTPUT);     // Initialise la broche "led" comme une sortie - Initialize the "LED" pin as an output
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

// Cette boucle s'exécute à l'infini
// the loop function runs over and over again forever
void loop() {
  if(digitalRead(8) == HIGH || digitalRead(7) == HIGH || digitalRead(6) == HIGH){
    digitalWrite(9, HIGH); 
  } else {
      digitalWrite(9, LOW);   // Eteint la Led - Turn the LED OFF 

  }
  delay(100);
}
