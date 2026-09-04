const int POT_PIN = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(POT_PIN);

  int percentage = map(
    rawValue,
    0,
    4095,
    0,
    100
  );

  Serial.print("ADC: ");
  Serial.print(rawValue);

  Serial.print(" | Percentage: ");
  Serial.print(percentage);

  Serial.println("%");

  delay(200);
}