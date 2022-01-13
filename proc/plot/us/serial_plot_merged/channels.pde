final int nChannels = 14;
final int intSize = 2;  // bytes
final List<Short>[] channels = new List[nChannels];
final byte[] currentBuffer = new byte[nChannels * intSize];
ByteBuffer byteBuffer; // Use this class to interpret bytes as integers

void initChannels() {
  for (List<Short> channel : channels) {
    channel = new ArrayList<Short>();
  }
}
