#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "hazel";
const char* password = "3853486170";

const int LED_PIN = 23;

WebServer server(80);

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
      </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleLedOn() {
  digitalWrite(LED_PIN, HIGH);

  server.send(
    200,
    "text/html",
    "<h1>LED ON</h1><a href='/'>Back</a>"
  );
}

void handleLedOff() {
  digitalWrite(LED_PIN, LOW);

  server.send(
    200,
    "text/html",
    "<h1>LED OFF</h1><a href='/'>Back</a>"
  );
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);

  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}