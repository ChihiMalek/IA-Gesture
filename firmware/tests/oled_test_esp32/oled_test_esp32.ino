#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// === Paramètres de l'écran ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C // Adresse I2C de l’écran

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println("Test OLED SSD1306...");

  // Initialisation de l’écran
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Erreur : écran OLED non détecté !"));
    for (;;); // Boucle bloquante si échec
  }

  display.clearDisplay();

  // === Test de texte ===
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Test OLED OK!");
  display.println("Arduino Mega 2560");
  display.println("Adresse: 0x3C");
  display.display();
  delay(2000);

  // === Test de formes ===
  display.clearDisplay();
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.fillCircle(64, 32, 10, SSD1306_WHITE);
  display.drawLine(0, 32, 128, 32, SSD1306_WHITE);
  display.display();
  delay(2000);

  // === Test défilement ===
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Scrolling");
  display.display();
  display.startscrollleft(0x00, 0x0F); // Défilement gauche
  delay(3000);
  display.stopscroll();
  display.startscrollright(0x00, 0x0F); // Défilement droite
  delay(3000);
  display.stopscroll();

  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(2);
  display.println("Done!");
  display.display();
}

void loop() {
  // Rien à faire ici, tout est dans setup()
}
