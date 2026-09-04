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

  digitalWrite(
    LED_PIN,
    ledState ? HIGH : LOW
  );
}

void toggleLed() {
  setLed(!ledState);
}

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
      <head>
        <title>ESP32 LED</title>
      </head>
      <body>
        <h1>ESP32 LED Controller</h1>

        <p>
          <a href="/on">
            <button>Turn ON</button>
          </a>
        </p>

        <p>
          <a href="/off">
            <button>Turn OFF</button>
          </a>
        </p>

        <p>
          <a href="/toggle">
            <button>Toggle</button>
          </a>
        </p>
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleLedOn() {
  setLed(true);

  server.send(
    200,
    "text/html",
    "<h1>LED ON</h1><a href='/'>Back</a>"
  );
}

void handleLedOff() {
  setLed(false);

  server.send(
    200,
    "text/html",
    "<h1>LED OFF</h1><a href='/'>Back</a>"
  );
}

void handleToggle() {
  toggleLed();

  server.send(
    200,
    "text/html",
    "<h1>LED TOGGLED</h1><a href='/'>Back</a>"
  );
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  pinMode(
    BUTTON_PIN,
    INPUT_PULLUP
  );

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

  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);
  server.on("/toggle", handleToggle);

  server.begin();
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

    Serial.println(
      ledState ? "ON" : "OFF"
    );

    delay(50);
  }

  lastButtonState = currentButtonState;
}