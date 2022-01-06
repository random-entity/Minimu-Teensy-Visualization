void displayData01() {
  int reading;
  float bat_voltage;
  char report[80];


  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);

  display.print("GLPS Heaphones v.");
  display.println(VERSION);

  display.println();

  display.print("Software v. ");
  display.println(SOFT_VERSION);
  display.println();
  display.print("Hedphone ID: ");
  display.println();

  reading = analogRead(A0);
  bat_voltage = 3.3 * 2 * reading / 1024.0;
  //  display.print("time= ");
  //  display.println(int(millis() / 1000));

  display.print("V-Bat= ");
  display.print(bat_voltage);
  display.print("   ");
  //int bat_percent = int(((bat_voltage - 2.2) / (4.14 - 2.2)) * 100);
  int bat_percent = int(((bat_voltage - 3.356) / (4.04 - 3.356)) * 100);
  if (bat_percent > 100)bat_percent = 100;
  if (bat_percent < 0)bat_percent = 0;
  display.setTextSize(1);
  display.print(bat_percent);
  display.println("%");
  display.setTextSize(1);
  if (bat_voltage < 3.45) display.println("BATTERY LOW");
  display.display();
}
