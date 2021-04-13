int led = D3;

void setup() {
  pinMode(led, OUTPUT);     // Initialise la broche "led" comme une sortie - Initialize the "LED" pin as an output
}

// Cette boucle s'exécute à l'infini
// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, LOW);   // Eteint la Led - Turn the LED OFF 
  delay(1000);              // Attendre 1 seconde - Wait for a second
  digitalWrite(led, HIGH);  // Allume la Led - Turn the LED off by making the voltage HIGH
  delay(2000);              // Pause de 2 secondes - Wait 2 secondes
}
