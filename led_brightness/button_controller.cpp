#include <Arduino.h>

#include "config.h"
#include "button_controller.h"
#include "led_controller.h"

bool lastRawButtonState = HIGH;
bool stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;

void setupButton() {
  pinMode(
    BUTTON_PIN,
    INPUT_PULLUP
  );
}

void handleButton() {
  bool rawState =
      digitalRead(BUTTON_PIN);

  if (rawState != lastRawButtonState) {
    lastDebounceTime = millis();
  }

  if (
    millis() - lastDebounceTime
      >= DEBOUNCE_DELAY_MS
  ) {
    if (rawState != stableButtonState) {
      stableButtonState = rawState;

      if (stableButtonState == LOW) {
        toggleLed();

        Serial.print(
          "Button pressed. LED: "
        );

        Serial.println(
          isLedOn() ? "ON" : "OFF"
        );
      }
    }
  }

  lastRawButtonState = rawState;
}