#ifndef CONFIG_H
#define CONFIG_H

// Pins
constexpr int LED_PIN = 23;
constexpr int BUTTON_PIN = 18;
constexpr int POT_PIN = 34;

// Wi-Fi
constexpr char WIFI_SSID[] = "hazel";
constexpr char WIFI_PASSWORD[] = "3853486170";

// Button
constexpr unsigned long DEBOUNCE_DELAY_MS = 50;

// Potentiometer
constexpr unsigned long POT_READ_INTERVAL_MS = 100;

// PWM
constexpr int PWM_FREQUENCY = 5000;
constexpr int PWM_RESOLUTION = 8;

#endif