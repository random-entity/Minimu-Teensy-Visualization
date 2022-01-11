void addPoint(int channelIndex, int plotIndex) {
  for (int i = 0; i < channels[channelIndex].size(); i++, pointsCnt++) {
    plots[plotIndex].addPoint((currentTimePrev
      + ((currentTime - currentTimePrev) * scatterCoef * i / channels[channelIndex].size())
      - startTime)
      / 1e9f, 
      channels[channelIndex].get(i));

    //if (pointsCnt > nPoints) {
    //  plots[plotIndex].removePoint(0);
    //}
  }
}
