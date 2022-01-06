void setup() {
  Serial.begin(57600);
}

int count = 0;

void loop() {

  Serial.write(count * 100);
  count++;
  if(count > 30) count = 0;
  delay(5);

}
