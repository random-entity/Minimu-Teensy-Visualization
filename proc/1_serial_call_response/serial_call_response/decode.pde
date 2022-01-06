void decode() {
  int checkSumProcessing = 0;
  for (int i = 0; i < 12; i++) {
    checkSumProcessing += serialIn[2 * i] + serialIn[2 * i + 1];

    int decoded = 256 * serialIn[2 * i] + serialIn[2 * i + 1] - 10000;
    decodedData[i] = decoded;
    //println("decoded : " + i + " : " + decoded);
  }

  checkSumProcessing %= 256;
  int checkSumIn = serialIn[serialIn.length - 1];

  checkSumTestPassed = (checkSumProcessing == checkSumIn);
  //println("check_sum test pass : " + checkSumTestPassed + ". checkSumIn = " + checkSumIn + ", checkSumProcessing = " + checkSumProcessing);
}
