final int nChannels = 14;
final int intSize = 2; // bytes
List<Short>[] channels = new List[nChannels];
final byte[] currentBuffer = new byte[nChannels * intSize];
ByteBuffer byteBuffer; // Use this class to interpret bytes as integers

void initChannels() {
  println("initChannels() :");
  println("channels.length = " + channels.length);
  for (int i = 0; i < channels.length; i++) {
    channels[i] = new ArrayList<Short>();
  }
}

void channelsToPlot() {
  println("channelsToPlot() :");

  for (int i = 0; i < channels.length; i++) {
    print("channel " + i + " has " + channels[i].size() + " data : ");
    if (channels[i].size() == 0) {
      println("NO DATA. Do nothing and return...");
      return;
    }
    for (int j = 0; j < channels[i].size(); j++) {
      print(channels[i].get(j) + " ");
    }
    println();
  }
  
  println("Every channel has at least one data.");

  plots[0].addPoints(getStepTimeInSec(), channels[1].get(0), channels[2].get(0), channels[3].get(0));
  plots[1].addPoints(getStepTimeInSec(), channels[4].get(0), channels[5].get(0), channels[6].get(0));
  plots[2].addPoints(getStepTimeInSec(), channels[7].get(0), channels[8].get(0), channels[7].get(0));
  plots[3].addPoints(getStepTimeInSec(), channels[10].get(0), channels[11].get(0), channels[12].get(0));

  clearChannels();
}

void clearChannels() {
  for (List<Short> channel : channels) {
    channel.clear();
  }
}
