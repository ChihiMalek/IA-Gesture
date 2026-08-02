#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===== Wi-Fi credentials =====
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ===== MQTT broker =====
const char* mqtt_server = "broker.emqx.io";
const int   mqtt_port   = 1883;
const char* topic_gesture = "assist/gesture";

// ===== OLED setup =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WiFiClient espClient;
PubSubClient client(espClient);

void showText(const String& line1, const String& line2 = "") {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 8);
  display.println(line1);
  if (line2.length()) {
    display.setCursor(0, 36);
    display.println(line2);
  }
  display.display();
}

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  showText("WiFi...", "Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  showText("WiFi OK", WiFi.localIP().toString());
  delay(800);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
  Serial.printf("Topic: %s | Msg: %s\n", topic, msg.c_str());

  if (String(topic) == topic_gesture) {
    if (msg == "HELP") {
      showText("Gesture", "HELP");
    } else if (msg == "YES") {
      showText("Gesture", "YES");
    } else if (msg == "NO") {
      showText("Gesture", "NO");
    } else if (msg == "STOP") {
      showText("Gesture", "STOP");
    } else {
      showText("Gesture", msg);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connect...");
    showText("MQTT...", "Connecting");
    String clientId = "ESP8266_" + String(ESP.getChipId(), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic_gesture);
      showText("MQTT OK", "Subscribed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retry in 3s");
      showText("MQTT Err", String(client.state()));
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true) delay(1);
  }
  showText("Booting", "OLED OK");
  delay(800);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}
