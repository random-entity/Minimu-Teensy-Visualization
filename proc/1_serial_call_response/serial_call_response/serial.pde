void call(Serial port) {
  port.write('A');
}

void serialEvent(Serial port) {
  int inByte = port.read();

  if (inByte == inStartByte) {
    serialIndex = 0;
    port.clear();
  } else {
    if (serialIndex < serialIn.length) {
      serialIn[serialIndex] = inByte;
      //println(inByte);
      serialIndex++;
    }
  }
}
