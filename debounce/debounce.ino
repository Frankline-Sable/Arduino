#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const int LED_PIN = 23;
const int BUTTON_PIN = 18;

bool ledState = false;

// Button state
bool lastRawButtonState = HIGH;
bool stableButtonState = HIGH;

// Debounce timing
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

WebServer server(80);

void setLed(bool state) {
  ledState = state;
  digitalWrite(
    LED_PIN,
    ledState ? HIGH : LOW
  );
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

void handleButton() {
  bool rawButtonState = digitalRead(BUTTON_PIN);

  // Raw input changed, so restart debounce timer
  if (rawButtonState != lastRawButtonState) {
    lastDebounceTime = millis();
  }

  // Has the input remained unchanged long enough?
  if (
    millis() - lastDebounceTime >= debounceDelay
  ) {

    // Stable state has actually changed
    if (rawButtonState != stableButtonState) {
      stableButtonState = rawButtonState;

      // INPUT_PULLUP means LOW = pressed
      if (stableButtonState == LOW) {
        toggleLed();

        Serial.print("Button pressed. LED: ");
        Serial.println(
          ledState ? "ON" : "OFF"
        );
      }
    }
  }

  lastRawButtonState = rawButtonState;
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
  handleButton();
}