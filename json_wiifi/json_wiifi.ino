#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "hazel";
const char* password = "3853486170";

const int LED_PIN = 23;
const int BUTTON_PIN = 18;

bool ledState = false;
bool lastButtonState = HIGH;

WebServer server(80);

void setLed(bool state) {
  ledState = state;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
}

void toggleLed() {
  setLed(!ledState);
}

void sendLedState() {
  String json = "{";
  json += "\"on\":";
  json += ledState ? "true" : "false";
  json += "}";

  server.send(
    200,
    "application/json",
    json
  );
}

void handleGetLed() {
  sendLedState();
}

void handleLedOn() {
  setLed(true);
  sendLedState();
}

void handleLedOff() {
  setLed(false);
  sendLedState();
}

void handleLedToggle() {
  toggleLed();
  sendLedState();
}

void handleNotFound() {
  server.send(
    404,
    "application/json",
    "{\"error\":\"Route not found\"}"
  );
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  setLed(false);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on(
    "/api/led",
    HTTP_GET,
    handleGetLed
  );

  server.on(
    "/api/led/on",
    HTTP_POST,
    handleLedOn
  );

  server.on(
    "/api/led/off",
    HTTP_POST,
    handleLedOff
  );

  server.on(
    "/api/led/toggle",
    HTTP_POST,
    handleLedToggle
  );

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("HTTP API started");
}

void loop() {
  server.handleClient();

  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (
    lastButtonState == HIGH &&
    currentButtonState == LOW
  ) {
    toggleLed();

    Serial.print("Button pressed. LED: ");
    Serial.println(ledState ? "ON" : "OFF");

    delay(50);
  }

  lastButtonState = currentButtonState;
}