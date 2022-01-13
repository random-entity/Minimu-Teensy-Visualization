class plotXYZ {
  GPlot plot;

  plotXYZ(PApplet p, int row, int col) {
    plot = new GPlot(p);

    plot.setPos(row * plotWidth, col * plotHeight);
    plot.setYLim(-200, 200);
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
}
