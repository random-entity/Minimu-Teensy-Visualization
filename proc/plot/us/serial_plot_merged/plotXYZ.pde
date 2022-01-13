class PlotXYZ {
  GPlot plot;
  static final int nPoints = 200;
  int pointCount = 0;

  PlotXYZ(PApplet p, int row, int col, float yLowerLimit, float yUpperLimit) {
    plot = new GPlot(p);

    plot.setPos(row * plotWidth, col * plotHeight);
    plot.setYLim(yLowerLimit, yUpperLimit);
    plot.setPointSize(1f);

    plot.addLayer("x", new GPointsArray());
    plot.getLayer("x").setPointSize(1f);
    plot.getLayer("x").setLineColor(color(255, 0, 0));

    plot.addLayer("y", new GPointsArray());
    plot.getLayer("y").setPointSize(1f);
    plot.getLayer("y").setLineColor(color(0, 255, 0));

    plot.addLayer("z", new GPointsArray());
    plot.getLayer("z").setPointSize(1f);
    plot.getLayer("z").setLineColor(color(0, 0, 255));
  }

  GLayer getLayer(int axis) {
    switch(axis) {
    case 0: 
      return plot.getLayer("x");
    case 1: 
      return plot.getLayer("y");
    case 2: 
      return plot.getLayer("z");
    default: 
      println("plotXYZ.getLayer() : wrong axis index.");
      return null;
    }
  }

  void addPoints(float t, float x, float y, float z) {
    getLayer(0).addPoint(t, x);
    getLayer(1).addPoint(t, y);
    getLayer(2).addPoint(t, z);
    plot.updateLimits();
    pointCount++;
    
    cutPoints();
  }

  void removeFirstPoint() {
    for (int i = 0; i < 3; i++) {
      getLayer(i).removePoint(0);
    }
    pointCount--;
  }

  void cutPoints() {
    if (pointCount > nPoints) {
      for (int i = 0; i < 3; i++) {
        for (int r = 0; r < pointCount - nPoints; r++) {
          removeFirstPoint();
        }
      }
    }
  }

  void defaultDraw() {
    plot.defaultDraw();
  }
}
