#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi_manager.h"

void connectWifi() {
  WiFi.mode(WIFI_STA);

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.print("Connecting to Wi-Fi");

  while (
    WiFi.status() != WL_CONNECTED
  ) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

bool isWifiConnected() {
  return WiFi.status()
      == WL_CONNECTED;
}