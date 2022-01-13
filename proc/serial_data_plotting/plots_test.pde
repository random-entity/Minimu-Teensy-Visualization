void addTestPointsStatic() {
  for (int i = 0; i < 200; i++) {
    plots[0].addPoints(i, 
      2 * i, 
      2 * (100 - i), 
      100 * sin(0.1 * i)
      );

    plots[1].addPoints(i, 
      pow(2 * i, sin(i)), 
      2 * (100 - 50 * sin(i)) * cos(0.3 * i), 
      100 * sin(0.5 * pow(sin(0.1 * i), 2))
      );

    plots[2].addPoints(i, 
      pow(2 * i, sin(i)), 
      2 * (100 - i) * cos(0.2 * i), 
      100 * pow(sin(0.1 * i), 2)
      );

    plots[3].addPoints(i, 
      pow(3 * i, sin(i * cos(i * i))), 
      2 * (100 - i) * cos(i * sin(i)), 
      100 * pow(sin(0.1 * i), 2)
      );
  }
}

int testX = 200;

void addTestPointsDynamic() {
  testX++;
  plots[0].addPoints(testX, 
    (2 * testX) % 200, 
    (2 * (100 - testX)) % 200, 
    100 * sin(0.1 * testX)
    );

  plots[1].addPoints(testX, 
    pow(2 * testX, sin(testX)), 
    2 * (100 - 50 * sin(testX)) * cos(0.3 * testX), 
    100 * sin(0.5 * pow(sin(0.1 * testX), 2))
    );

  plots[2].addPoints(testX, 
    pow(2 * testX, sin(testX)), 
    0.1 * (100 - testX) * cos(2 + 0.2 * testX), 
    100 * pow(sin(0.1 * testX), 2)
    );

  plots[3].addPoints(testX, 
    pow(3 * testX, sin(testX * cos(testX * testX))) % 150, 
    2 * (100 - testX) * cos(testX * sin(testX)), 
    40 * pow(sin(0.1 * testX), 2)
    );
}
