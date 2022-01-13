Serial ser;
final int portNumber = 2;
final int baudRate = 57600;

void initSerial() {
  println("initSerial() : ");
  println("printArray(Serial.list()) : ");
  printArray(Serial.list());
  printArray("selected port number " + portNumber);
  String portName = Serial.list()[portNumber];
  println("port name : " + portName);

  ser = new Serial(this, portName, baudRate);
  ser.buffer(nChannels * intSize);
}

void serialToChannels(Serial s) {
  println("serialToChannels() :");
  println("reading bytes...");
  s.readBytes(currentBuffer);
  println("decoding...");
  byteBuffer = ByteBuffer.wrap(currentBuffer).order(ByteOrder.BIG_ENDIAN);
  for (int i = 0; i < channels.length; i++) {
    channels[i].add(byteBuffer.getShort());
  }
  println("END serialToChannels()");
}

void serialEvent(Serial s) {
  println("serial event : time = " + getStepTimeInSec() + " (sec)");
  serialToChannels(s);
}
