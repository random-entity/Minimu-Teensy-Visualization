import java.nio.*;
import java.util.List;
import java.util.ArrayList;
import processing.serial.*;
import grafica.*;

void settings() {
  size(plotWidth * 2, plotHeight * 2);
}

void setup() {
  initChannels();
  initPlots();
  initSerial();
  initTimers();
}

void draw() {
  if (System.nanoTime() - stepTime >= callInterval) {
    stepTimePrev = stepTime;
    stepTime = System.nanoTime();

    ser.write('A');
    //addTestPointsDynamic();
  }

  channelsToPlot();
  drawPlots();
}
