import java.nio.*;
import java.util.List;
import java.util.ArrayList;
import processing.serial.*;
import grafica.*;

void settings() {
  size(plotWidth * plotNRows, plotHeight * plotNCols);
}

void setup() {
  initChannels();
  initPlots();
  initSerial();
  initTimers();
}

void draw() {
  if (System.nanoTime() - stepTime >= callInterval) {
    stepTime = System.nanoTime();
    ser.write('A');
  }

  channelsToPlot();
  drawPlots();
}
