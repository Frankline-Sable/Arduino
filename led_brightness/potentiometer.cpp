#include <Arduino.h>

#include "config.h"
#include "potentiometer.h"
#include "led_controller.h"

unsigned long lastPotReadTime = 0;

int potentiometerValue = 0;

void setupPotentiometer() {
  pinMode(
    POT_PIN,
    INPUT
  );
}

void handlePotentiometer() {
  unsigned long currentTime = millis();

  if (
    currentTime - lastPotReadTime
      < POT_READ_INTERVAL_MS
  ) {
    return;
  }

  lastPotReadTime = currentTime;

  potentiometerValue =
      analogRead(POT_PIN);

  int brightness = map(
    potentiometerValue,
    0,
    4095,
    0,
    255
  );

  setLedBrightness(brightness);
}

int getPotentiometerValue() {
  return potentiometerValue;
}