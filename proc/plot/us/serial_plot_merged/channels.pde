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
  for (int i = 0; i < channels.length; i++) {
    if (channels[i].size() == 0) {
      return;
    }

    print("channel " + i + " has " + channels[i].size() + " data : ");
    for (int j = 0; j < channels[i].size(); j++) {
      print(channels[i].get(j) + " ");
    }
    println();
  }

  if (channels[0].get(0) != 0x7FFF) {
    println("START SIGNAL UNMATCH! : channel 0 is not " + startSignal);
    clearChannels();
    return;
  } else {
    println("START SIGNAL OK");
  }

  short checkSum = 0;
  for (int i = 1; i <= 12; i++) {
    checkSum += channels[i].get(0);
  }
  if (checkSum != channels[13].get(0)) {
    println("CHECKSUM UNMATCH!");
    println("Processing's checkSum = " + checkSum);
    println("Teensy's checkSum = " + channels[13].get(0));
    clearChannels();
    return;
  } else {
    println("CHECK SUM OK");
  }

  plots[0].addPoints(getStepTimeInSec(), channels[1].get(0), channels[2].get(0), channels[3].get(0));
  plots[1].addPoints(getStepTimeInSec(), channels[4].get(0), channels[5].get(0), channels[6].get(0));
  plots[2].addPoints(getStepTimeInSec(), channels[7].get(0), channels[8].get(0), channels[9].get(0));
  plots[3].addPoints(getStepTimeInSec(), channels[10].get(0), channels[11].get(0), channels[12].get(0));

  clearChannels();
}

void clearChannels() {
  for (List<Short> channel : channels) {
    channel.clear();
  }
}
