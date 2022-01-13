final PlotXYZ[] plots = new PlotXYZ[4];
final int plotWidth = 450;
final int plotHeight = 300;

void initPlots() {
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      int index = i + 2 * j;
      plots[index] = new PlotXYZ(this, i, j, -2000, 2000);
    }
  }
}

void drawPlots() {
  for (PlotXYZ plot : plots) {
    plot.defaultDraw();
  }
}
