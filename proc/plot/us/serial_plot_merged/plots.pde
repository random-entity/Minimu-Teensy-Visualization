final PlotXYZ[] plots = new PlotXYZ[4];
final int plotWidth = 450;
final int plotHeight = 300;

void initPlots() {
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      int index = i + 2 * j;
      plots[index] = new PlotXYZ(this, i, j, -200, 200);
    }
  }
}

void drawPlots() {
  for (PlotXYZ plot : plots) {
    plot.defaultDraw();
  }
}

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

int i = 200;

void addTestPointsDynamic() {
  i++;
  plots[0].addPoints(i, 
    (2 * i) % 200, 
    (2 * (100 - i)) % 200, 
    100 * sin(0.1 * i)
    );

  plots[1].addPoints(i, 
    pow(2 * i, sin(i)), 
    2 * (100 - 50 * sin(i)) * cos(0.3 * i), 
    100 * sin(0.5 * pow(sin(0.1 * i), 2))
    );

  plots[2].addPoints(i, 
    pow(2 * i, sin(i)), 
    0.1 * (100 - i) * cos(2 + 0.2 * i), 
    100 * pow(sin(0.1 * i), 2)
    );

  plots[3].addPoints(i, 
    pow(3 * i, sin(i * cos(i * i))) % 150, 
    2 * (100 - i) * cos(i * sin(i)), 
    40 * pow(sin(0.1 * i), 2)
    );
}
