final PlotXYZ[] plots = new PlotXYZ[4];

final int plotNRows = 1;
final int plotNCols = 4;

final int plotWidth = 1000;
final int plotHeight = 200;

final int yLowerLimitGyro = -6000;
final int yUpperLimitGyro = 6000;

final int yLowerLimitAccel = -2000;
final int yUpperLimitAccel = 2000;

static final int nPoints = 400;

void initPlots() {
  for (int i = 0; i < plotNRows; i++) {
    for (int j = 0; j < plotNCols; j++) {
      int index = i + plotNRows * j;
      int yLowerLimit = index % 2 == 0 ? yLowerLimitGyro : yLowerLimitAccel;
      int yUpperLimit = index % 2 == 0 ? yUpperLimitGyro : yUpperLimitAccel;
      plots[index] = new PlotXYZ(this, i, j, yLowerLimit, yUpperLimit);
    }
  }
}

void drawPlots() {
  for (PlotXYZ plot : plots) {
    plot.defaultDraw();
  }
}
