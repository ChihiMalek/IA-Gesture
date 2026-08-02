#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuration OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables pour animations
unsigned long previousMillis = 0;
const long interval = 1000;
int screenIndex = 0;
int frameCount = 0;
float temperature = 0;
float humidity = 0;
int analogValue = 0;
int xPos = 0;
int direction = 1;

// Dessin d'un logo Arduino
const unsigned char arduinoLogo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(115200);
  Serial.println("Test OLED Arduino DUE - Version Amelioree");
  
  // Initialisation OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("ERREUR: OLED non detecte!"));
    Serial.println(F("Verifiez le cablage:"));
    Serial.println(F("VCC -> 3.3V"));
    Serial.println(F("GND -> GND"));
    Serial.println(F("SDA -> Pin 20"));
    Serial.println(F("SCL -> Pin 21"));
    while(1);
  }
  
  Serial.println("OLED initialise avec succes!");
  
  // Afficher écran de démarrage
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("ARDUINO");
  display.setCursor(30, 30);
  display.println("DUE");
  display.setTextSize(1);
  display.setCursor(20, 50);
  display.println("OLED Test 128x64");
  display.display();
  delay(2000);
  
  // Générer des données simulées
  randomSeed(analogRead(0));
  temperature = 22.5 + random(-10, 10)/10.0;
  humidity = 45.0 + random(-20, 20)/10.0;
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Changement d'écran toutes les 5 secondes
  if (currentMillis - previousMillis >= 5000) {
    previousMillis = currentMillis;
    screenIndex = (screenIndex + 1) % 5;
    frameCount = 0;
  }
  
  // Mettre à jour les données simulées
  frameCount++;
  if (frameCount % 10 == 0) {
    temperature += random(-10, 10)/10.0;
    temperature = constrain(temperature, 15.0, 35.0);
    humidity += random(-20, 20)/10.0;
    humidity = constrain(humidity, 30.0, 80.0);
    analogValue = analogRead(A0);
  }
  
  // Affichage selon l'écran sélectionné
  switch(screenIndex) {
    case 0:
      displayScreenInfo();
      break;
    case 1:
      displaySystemStatus();
      break;
    case 2:
      displayGraph();
      break;
    case 3:
      displayAnimation();
      break;
    case 4:
      displayDiagnostic();
      break;
  }
  
  // Afficher indicateur de page en bas
  displayPageIndicator();
  
  // Rafraîchir l'affichage
  display.display();
  delay(50);
}

// Écran 1: Informations système
void displayScreenInfo() {
  display.clearDisplay();
  display.setTextSize(1);
  
  // Titre
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("=== SYSTEME DUE ===");
  
  // Informations
  display.setCursor(0, 15);
  display.print("Temps: ");
  display.print(millis() / 1000);
  display.println("s");
  
  display.setCursor(0, 25);
  display.print("Uptime: ");
  display.print(millis() / 60000);
  display.println(" min");
  
  display.setCursor(0, 35);
  display.print("Free RAM: ");
  display.print(freeMemory());
  display.println(" bytes");
  
  display.setCursor(0, 45);
  display.print("Frame: ");
  display.print(frameCount);
  
  // LED clignotante simulée
  int ledState = (millis() / 500) % 2;
  display.fillRect(110, 15, 5, 5, ledState ? SSD1306_WHITE : SSD1306_BLACK);
  display.drawRect(109, 14, 7, 7, SSD1306_WHITE);
  display.setCursor(100, 25);
  display.println("LED");
}

// Écran 2: Status avec données simulées
void displaySystemStatus() {
  display.clearDisplay();
  
  // En-tête
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("== STATUS SYSTEME ==");
  
  // Température
  display.setCursor(0, 15);
  display.print("Temperature: ");
  display.print(temperature, 1);
  display.println(" C");
  
  // Barre de température
  int tempBar = map((int)temperature, 15, 35, 0, 50);
  display.drawRect(0, 25, 52, 8, SSD1306_WHITE);
  display.fillRect(1, 26, tempBar, 6, SSD1306_WHITE);
  
  // Humidité
  display.setCursor(0, 40);
  display.print("Humidite: ");
  display.print(humidity, 1);
  display.println(" %");
  
  // Barre d'humidité
  int humBar = map((int)humidity, 30, 80, 0, 50);
  display.drawRect(0, 50, 52, 8, SSD1306_WHITE);
  display.fillRect(1, 51, humBar, 6, SSD1306_WHITE);
  
  // Valeurs numériques à droite
  display.setCursor(70, 15);
  display.print("A0: ");
  display.println(analogValue);
  
  display.setCursor(70, 25);
  display.print("3.3V: OK");
  
  display.setCursor(70, 35);
  display.print("I2C: OK");
  
  // Icône thermomètre
  display.drawRect(105, 15, 3, 10, SSD1306_WHITE);
  display.fillRect(105, 15, 3, map((int)temperature, 15, 35, 10, 0), SSD1306_BLACK);
  display.fillCircle(106, 25, 5, SSD1306_WHITE);
}

// Écran 3: Graphique animé
void displayGraph() {
  static int graphData[100];
  static int dataIndex = 0;
  
  display.clearDisplay();
  
  // Titre
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("== GRAPHIQUE LIVE ==");
  
  // Générer nouvelle donnée
  graphData[dataIndex] = map(analogRead(A0), 0, 1023, 0, 40);
  dataIndex = (dataIndex + 1) % 100;
  
  // Dessiner le graphique
  display.drawRect(0, 15, 128, 40, SSD1306_WHITE);
  
  for(int i = 0; i < 99; i++) {
    int x1 = map(i, 0, 99, 1, 127);
    int x2 = map(i+1, 0, 99, 1, 127);
    int y1 = 54 - graphData[(dataIndex + i) % 100];
    int y2 = 54 - graphData[(dataIndex + i + 1) % 100];
    
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }
  
  // Afficher valeur actuelle
  display.setCursor(90, 55);
  display.print("Val: ");
  display.print(graphData[(dataIndex + 99) % 100]);
}

// Écran 4: Animation
void displayAnimation() {
  display.clearDisplay();
  
  // Titre
  display.setTextSize(1);
  display.setCursor(30, 0);
  display.println("ANIMATION");
  
  // Balle qui rebondit
  static int ballX = 64;
  static int ballY = 32;
  static int ballSpeedX = 2;
  static int ballSpeedY = 1;
  
  // Mettre à jour position
  ballX += ballSpeedX;
  ballY += ballSpeedY;
  
  // Rebonds sur les bords
  if(ballX <= 3 || ballX >= 124) ballSpeedX = -ballSpeedX;
  if(ballY <= 10 || ballY >= 58) ballSpeedY = -ballSpeedY;
  
  // Dessiner la balle
  display.fillCircle(ballX, ballY, 3, SSD1306_WHITE);
  
  // Dessiner le cadre
  display.drawRect(2, 10, 124, 48, SSD1306_WHITE);
  
  // Informations animation
  display.setCursor(0, 55);
  display.print("X:");
  display.print(ballX);
  display.print(" Y:");
  display.print(ballY);
  display.print(" F:");
  display.print(frameCount);
}

// Écran 5: Diagnostic
void displayDiagnostic() {
  display.clearDisplay();
  
  // Titre
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.println("DIAGNOSTIC DUE");
  
  // Informations techniques
  display.setCursor(0, 15);
  display.println("Carte: Arduino DUE");
  display.setCursor(0, 25);
  display.println("CPU: SAM3X8E ARM");
  display.setCursor(0, 35);
  display.println("Freq: 84 MHz");
  display.setCursor(0, 45);
  display.println("Tension: 3.3V");
  
  // Signal de qualité
  int signalStrength = 50 + random(-20, 20);
  display.setCursor(70, 15);
  display.print("Signal: ");
  display.print(signalStrength);
  display.println("%");
  
  // Barre de signal
  display.drawRect(70, 25, 40, 10, SSD1306_WHITE);
  int bars = map(signalStrength, 0, 100, 0, 8);
  for(int i = 0; i < bars; i++) {
    display.fillRect(72 + i*4, 27 + (7-i), 2, i+1, SSD1306_WHITE);
  }
  
  // QR code simulé (carré)
  display.drawRect(85, 40, 20, 20, SSD1306_WHITE);
  display.fillRect(88, 43, 4, 4, SSD1306_WHITE);
  display.fillRect(98, 43, 4, 4, SSD1306_WHITE);
  display.fillRect(88, 53, 4, 4, SSD1306_WHITE);
}

// Indicateur de page en bas
void displayPageIndicator() {
  // Ligne de séparation
  display.drawLine(0, 63, 127, 63, SSD1306_WHITE);
  
  // Points indicateurs
  for(int i = 0; i < 5; i++) {
    if(i == screenIndex) {
      display.fillCircle(32 + i*16, 60, 2, SSD1306_WHITE);
    } else {
      display.drawCircle(32 + i*16, 60, 2, SSD1306_WHITE);
    }
  }
  
  // Nom de la page
  const char* pageNames[] = {"Info", "Status", "Graph", "Anim", "Diag"};
  display.setTextSize(1);
  display.setCursor(5, 55);
  display.print(pageNames[screenIndex]);
  
  // Flèches de navigation
  display.setCursor(110, 55);
  display.print(">>");
}

// Fonction pour obtenir la mémoire libre (simulée pour DUE)
int freeMemory() {
  // Pour DUE, cette fonction n'existe pas par défaut
  // On simule une valeur
  return 8192 - (millis() % 1000);
}