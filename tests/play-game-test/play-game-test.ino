String pp;
String* split;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000000);
  delay(2000); // lets code upload
}

void loop() {
  // pp = Serial.readStringUntil('\n');
  // pp = pp.substring(0, pp.length()-1);
  // strSplit(pp, ",", &split);
  // Serial.println(split[0]);
  playGame();
}
