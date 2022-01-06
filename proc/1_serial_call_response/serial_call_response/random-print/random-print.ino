void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.println(255);

  for(int i = 0; i < 13; i++) {
    Serial.println((int)random(255));
  }

  Serial.println();

  delay(1000);
}
