#include <Arduino.h>
#include <WebServer.h>

#include "api_server.h"
#include "led_controller.h"
#include "potentiometer.h"

WebServer server(80);

void sendLedState() {
  String json = "{";

  json += "\"on\":";
  json += isLedOn()
      ? "true"
      : "false";

  json += ",\"brightness\":";
  json += getLedBrightness();

  json += ",\"potentiometer\":";
  json += getPotentiometerValue();

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

void setupApiServer() {
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

  server.onNotFound(
    handleNotFound
  );

  server.begin();

  Serial.println(
    "HTTP API started"
  );
}

void handleApiServer() {
  server.handleClient();
}