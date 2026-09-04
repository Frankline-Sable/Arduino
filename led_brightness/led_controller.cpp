#include <Arduino.h>

#include "config.h"
#include "led_controller.h"

bool ledState = false;
int ledBrightness = 255;

void setupLed() {
  ledcAttach(
    LED_PIN,
    PWM_FREQUENCY,
    PWM_RESOLUTION
  );

  setLed(false);
}

void setLed(bool state) {
  ledState = state;

  if (ledState) {
    ledcWrite(
      LED_PIN,
      ledBrightness
    );
  } else {
    ledcWrite(
      LED_PIN,
      0
    );
  }
}

void toggleLed() {
  setLed(!ledState);
}

bool isLedOn() {
  return ledState;
}

void setLedBrightness(int brightness) {
  ledBrightness = constrain(
    brightness,
    0,
    255
  );

  if (ledState) {
    ledcWrite(
      LED_PIN,
      ledBrightness
    );
  }
}

int getLedBrightness() {
  return ledBrightness;
}