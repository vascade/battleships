#define BUZZ_PIN 2

void setup() {
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  delay(1);
  play(BUZZ_PIN, );
  delay(1);
  play(BUZZ_PIN, 440);
}
