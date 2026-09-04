const int LED_PIN=23;
const int POT_PIN=34;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  ledcAttach(
    LED_PIN, 5000,8
  );

}

void loop() {
  // put your main code here, to run repeatedly:
  int rawValue=analogRead(POT_PIN);

  int dutyCyle = map(rawValue,0,4095,0,255);

  ledcWrite(LED_PIN,dutyCyle);

  Serial.print("ADC: ");
  Serial.print(rawValue);

  Serial.print(" | PWM: ");
  Serial.println(dutyCyle);

  delay(50);
}
