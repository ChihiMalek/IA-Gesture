#define LED_PIN 8     // LED branchée sur GPIO8
#define BLINK_DELAY 500  // Délai en ms (0,5s allumé, 0,5s éteint)

void setup() {
  pinMode(LED_PIN, OUTPUT);   // Définit GPIO8 en sortie
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // LED ON
  delay(BLINK_DELAY);           // Attend 500 ms
  digitalWrite(LED_PIN, LOW);   // LED OFF
  delay(BLINK_DELAY);           // Attend 500 ms
}
