#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= WIFI =================
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ================= MQTT =================
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* topic_gesture = "assist/gesture";
const char* topic_object  = "assist/object";

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= PINS =================
#define TRIG_PIN   14   // D5
#define ECHO_PIN   12   // D6
#define BUZZER_PIN 2    // D4

#define BTN_MODE   0   // D3 → Mode Aveugle / Non Verbal
#define BTN_SOS    16  // D0 → SOS

// ================= MODES =================
enum Mode {
  MODE_AVEUGLE,
  MODE_NON_VERBAL,
  MODE_SECOURS
};

Mode currentMode = MODE_NON_VERBAL;

// ================= VARIABLES =================
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long modeButtonPressTime = 0;
const unsigned long longPressTime = 1000; // 1 sec
const unsigned long debounceDelay = 50;

// pour détecter front descendant bouton SOS
bool lastSosState = HIGH;

// gestion affichage
unsigned long lastDisplayMs = 0;
const unsigned long displayDuration = 1500; // 1.5s par message
String oledLine1 = "";
String oledLine2 = "";

// ================= OLED =================
void showText(String l1, String l2 = "", int s1 = 2, int s2 = 1, bool force = false) {
  unsigned long now = millis();
  if (!force && (l1 == oledLine1 && l2 == oledLine2)) return; // pas de changement

  oledLine1 = l1;
  oledLine2 = l2;
  lastDisplayMs = now;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(s1);
  display.setCursor(0, 8);
  display.println(l1);
  if (l2.length()) {
    display.setTextSize(s2);
    display.setCursor(0, 36);
    display.println(l2);
  }
  display.display();

  // Serial toujours
  Serial.println(l1 + (l2.length() ? " | " + l2 : ""));
}

// ================= BUZZER =================
void beepAlert(int n = 1) {
  for (int i = 0; i < n; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

// ================= ULTRASON =================
long getDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 25000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

// ================= WIFI =================
void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("WiFi connecting...");
  showText("WiFi", "Connecting", 2, 1, true);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  showText("WiFi OK", WiFi.localIP().toString(), 2, 1, true);
  Serial.println("WiFi connected, IP: " + WiFi.localIP().toString());
}

// ================= MQTT CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.println("MQTT IN | " + String(topic) + " : " + msg);

  // SOS ou Aveugle prioritaire → OLED forcé
  if (currentMode == MODE_AVEUGLE) {
    if (msg == "ALERT" || msg == "DANGER" || msg == "STOLEN") {
      showText("[Aveugle] ALERT!", msg, 2, 1, true);
      beepAlert();
    }
  }

  if (currentMode == MODE_NON_VERBAL) {
    showText("[Non Verbal]", msg, 2, 1, true);
  }
}

// ================= MQTT RECONNECT =================
void reconnect() {
  while (!client.connected()) {
    Serial.println("MQTT connecting...");
    String clientId = "ESP8266_" + String(ESP.getChipId(), HEX);
    if (client.connect(clientId.c_str())) {
      client.subscribe(topic_gesture);
      client.subscribe(topic_object);
      Serial.println("MQTT connected and subscribed.");
      showText("MQTT OK", "Subscribed", 2, 1, true);
    } else {
      Serial.println("MQTT failed, rc=" + String(client.state()));
      delay(3000);
    }
  }
}

// ================= CHECK MODE BUTTON =================
void checkModeButton() {
  bool pressed = digitalRead(BTN_MODE) == LOW;

  if (pressed && modeButtonPressTime == 0) {
    modeButtonPressTime = millis();
  } else if (!pressed && modeButtonPressTime != 0) {
    unsigned long duration = millis() - modeButtonPressTime;
    modeButtonPressTime = 0;

    if (duration < longPressTime) {
      currentMode = MODE_AVEUGLE;
      showText("[Mode]", "Aveugle (court)", 2, 1, true);
    } else {
      currentMode = MODE_NON_VERBAL;
      showText("[Mode]", "Non Verbal (long)", 2, 1, true);
    }
    delay(debounceDelay);
  }
}

// ================= CHECK SOS BUTTON =================
void checkSosButton() {
  bool currentSosState = digitalRead(BTN_SOS);

  if (lastSosState == HIGH && currentSosState == LOW) {
    currentMode = MODE_SECOURS;
    showText("[SOS]", "AU SECOURS!", 2, 1, true);
    beepAlert(2);
  }

  lastSosState = currentSosState;
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showText("Booting", "OLED OK", 2, 1, true);
  delay(600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_SOS, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, LOW);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// ================= LOOP =================
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  checkModeButton();
  checkSosButton();

  // PRIORITÉ boutons → SOS ou mode forcé
  if (currentMode == MODE_AVEUGLE) {
    long d = getDistanceCm();
    if (d > 0) {
      showText("[Aveugle] Dist", String(d) + " cm", 2, 1);
      if (d < 15) {
        showText("[Aveugle] ALERT!", "Distance < 15cm", 2, 1, true);
        beepAlert();
      }
    }
  }

  // Nettoyage écran après durée
  if (millis() - lastDisplayMs > displayDuration && currentMode != MODE_AVEUGLE && currentMode != MODE_SECOURS) {
    display.clearDisplay();
    display.display();
  }

  delay(150);
}
