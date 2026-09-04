#include "led_controller.h"
#include "button_controller.h"
#include "potentiometer.h"
#include "wifi_manager.h"
#include "api_server.h"

void setup() {
  Serial.begin(115200);

  setupLed();
  setupButton();
  setupPotentiometer();

  connectWifi();

  setupApiServer();

  Serial.println(
    "Smart Light ready!"
  );
}

void loop() {
  handleApiServer();
  handleButton();
  handlePotentiometer();
}