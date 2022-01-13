final GPlot[] plots = new GPlot[4];
final int plotWidth = 450;
final int plotHeight = 300;

void initPlots() {
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      int index = i + 2 * j;
      plots[index] = new GPlot(this);
      plots[index].setPos(i * plotWidth, j * plotHeight);
      plots[index].setYLim(-200, 200);
      plots[index].setPointSize(1f);

      plots[index].addLayer("x", new GPointsArray());
      plots[index].getLayer("x").setPointSize(1f);
      plots[index].getLayer("x").setLineColor(color(255, 0, 0));

      plots[index].addLayer("y", new GPointsArray());
      plots[index].getLayer("y").setPointSize(1f);
      plots[index].getLayer("y").setLineColor(color(0, 255, 0));

      plots[index].addLayer("z", new GPointsArray());
      plots[index].getLayer("z").setPointSize(1f);
      plots[index].getLayer("z").setLineColor(color(0, 0, 255));
    }
  }
}

void drawPlots() {
  for (GPlot plot : plots) {
    plot.defaultDraw();
  }
}

void addTestPointsStatic() {
  for (int i = 0; i < 200; i++) {
    plots[0].addPoint(i, 2 * i);
    plots[0].getLayer("y").addPoint(i, 2 * (100 - i));
    plots[0].getLayer("z").addPoint(i, 100 * sin(0.1 * i));

    plots[1].addPoint(i, pow(2 * i, sin(i)));
    plots[1].getLayer("y").addPoint(i, 2 * (100 - 50 * sin(i)) * cos(0.3 * i));
    plots[1].getLayer("z").addPoint(i, 100 * sin(0.5 * pow(sin(0.1 * i), 2)));

    plots[2].addPoint(i, pow(2 * i, sin(i)));
    plots[2].getLayer("y").addPoint(i, 2 * (100 - i) * cos(0.2 * i));
    plots[2].getLayer("z").addPoint(i, 100 * pow(sin(0.1 * i), 2));

    plots[3].addPoint(i, pow(3 * i, sin(i * cos(i * i))));
    plots[3].getLayer("y").addPoint(i, 2 * (100 - i) * cos(i * sin(i)));
    plots[3].getLayer("z").addPoint(i, 100 * pow(sin(0.1 * i), 2));
  }
}

int i = 0;

void addTestPointsDynamic() {
  i++;
  plots[0].addPoint(i, (2 * i) % 200);
  plots[0].getLayer("y").addPoint(i, (2 * (100 - i)) % 200);
  plots[0].getLayer("z").addPoint(i, 100 * sin(0.1 * i));

  plots[1].addPoint(i, pow(2 * i, sin(i)));
  plots[1].getLayer("y").addPoint(i, 2 * (100 - 50 * sin(i)) * cos(0.3 * i));
  plots[1].getLayer("z").addPoint(i, 100 * sin(0.5 * pow(sin(0.1 * i), 2)));

  plots[2].addPoint(i, pow(2 * i, sin(i)));
  plots[2].getLayer("y").addPoint(i, 2 * (100 - i) * cos(0.2 * i));
  plots[2].getLayer("z").addPoint(i, 100 * pow(sin(0.1 * i), 2));

  plots[3].addPoint(i, pow(3 * i, sin(i * cos(i * i))));
  plots[3].getLayer("y").addPoint(i, 2 * (100 - i) * cos(i * sin(i)));
  plots[3].getLayer("z").addPoint(i, 100 * pow(sin(0.1 * i), 2));
  
  plots[0].removePoint(0);
  plots[1].removePoint(0);
  plots[2].removePoint(0);
  plots[3].removePoint(0);
}
