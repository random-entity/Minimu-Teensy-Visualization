Serial ser;
final int portNumber = 2;
final int baudRate = 57600;

void initSerial() {
  println("initSerial() : ");
  println("printArray(Serial.list()) : ");
  printArray(Serial.list());
  printArray("selected port number " + portNumber);
  String portName = Serial.list()[portNumber];
  printArray("port name : " + portName);

  ser = new Serial(this, portName, baudRate);
  ser.buffer(nChannels * intSize);
}

void readSerial(Serial s) {
  s.readBytes(currentBuffer);
  byteBuffer = ByteBuffer.wrap(currentBuffer).order(ByteOrder.BIG_ENDIAN);

  int channelNumber = 0;
  for (List<Short> channel : channels) {
    channel.add(byteBuffer.getShort());

    println("channel " + (channelNumber++));
    for (short data : channel) {
      println(data);
    }
  }
}

void serialEvent(Serial s) {
  readSerial(s);
}
