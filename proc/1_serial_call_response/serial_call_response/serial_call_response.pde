import processing.serial.*;

Serial port;
int portNumber = 2;
int LEN_DATA = 30;
int[] serialIn = new int[LEN_DATA - 1];
int serialIndex = 0;
int[] decodedData = new int[12];

int inStartByte = 255;

int callInterval = 100;
int timer = 0;

int graphX = 0;

boolean checkSumTestPassed;

void setup() {
  size(1024, 512);

  printArray(Serial.list());
  String portName = Serial.list()[portNumber];
  port =  new Serial(this, portName, 57600);
}

void draw() {
  if (millis() - timer >= callInterval) {
    timer = millis();

    call(port);
    decode();
    updateDisplay();
  }
}

void updateDisplay() {
  fill(checkSumTestPassed ? color(0, 255, 0) : color(255, 0, 0));


  background(0);


  for (int i = 0; i < decodedData.length; i++) {
    
    //line(graphX, i * height / decodedData.length, 
    
    
    
    
    
    rect(width / 2, i * height / decodedData.length, decodedData[i], height / decodedData.length);
  }
  
    graphX++;

}
