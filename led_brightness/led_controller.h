#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

void setupLed();

void setLed(bool state);

void toggleLed();

bool isLedOn();

void setLedBrightness(int brightness);

int getLedBrightness();

#endif