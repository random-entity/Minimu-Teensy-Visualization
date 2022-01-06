#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

#define VERSION 0.32
#define SOFT_VERSION 1

//#define ZOE_RESET 40
//#define ZOE_SAFEBOOT 41
//#define ZOE_TIMEPULSE 42
//#define ZOE_INT 43
//
//// Use these with the Teensy Audio Shield
//#define SDCARD_CS_PIN    10
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_MISO_PIN  12
//#define SDCARD_SCK_PIN   13

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

#define LEN_DATA 30

////////////////////////////////////////////////////////////////IMU
#define IMU_V5

int SENSOR_SIGN[9] = {1, 1, 1, -1, -1, -1, 1, 1, 1}; //Correct directions x,y,z - gyro, accelerometer, magnetometer
// Uncomment the below line to use this axis definition:
// accelerometer: 8 g sensitivity
// 3.9 mg/digit; 1 g = 256
#define GRAVITY 256  //this equivalent to 1G in the raw data coming from the accelerometer

#define ToRad(x) ((x)*0.01745329252)  // *pi/180
#define ToDeg(x) ((x)*57.2957795131)  // *180/pi

// gyro: 2000 dps full scale
// 70 mdps/digit; 1 dps = 0.07
#define Gyro_Gain_X 0.07 //X axis Gyro gain
#define Gyro_Gain_Y 0.07 //Y axis Gyro gain
#define Gyro_Gain_Z 0.07 //Z axis Gyro gain
#define Gyro_Scaled_X(x) ((x)*ToRad(Gyro_Gain_X)) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Y(x) ((x)*ToRad(Gyro_Gain_Y)) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Z(x) ((x)*ToRad(Gyro_Gain_Z)) //Return the scaled ADC raw data of the gyro in radians for second

// LSM303/LIS3MDL magnetometer calibration constants; use the Calibrate example from
// the Pololu LSM303 or LIS3MDL library to find the right values for your board

#define M_X_MIN -1000
#define M_Y_MIN -1000
#define M_Z_MIN -1000
#define M_X_MAX +1000
#define M_Y_MAX +1000
#define M_Z_MAX +1000

#define Kp_ROLLPITCH 0.02
#define Ki_ROLLPITCH 0.00002
#define Kp_YAW 1.2
#define Ki_YAW 0.00002

/*For debugging purposes*/
//OUTPUTMODE=1 will print the corrected data,
//OUTPUTMODE=0 will print uncorrected data of the gyros (with drift)
#define OUTPUTMODE 1

#define PRINT_DCM 0     //Will print the whole direction cosine matrix
#define PRINT_ANALOGS 0 //Will print the analog raw data
#define PRINT_EULER 1   //Will print the Euler angles Roll, Pitch and Yaw

#define STATUS_LED 13

float G_Dt = 0.02;  // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer = 0; //general purpuse timer
long timer_old;
long timer24 = 0; //Second timer used to print values
int AN[6]; //array that stores the gyro and accelerometer data
int AN_OFFSET[6] = {0, 0, 0, 0, 0, 0}; //Array that stores the Offset of the sensors

int gyro_x;
int gyro_y;
int gyro_z;
int accel_x;
int accel_y;
int accel_z;

int g_x;
int g_y;
int g_z;
int a_x;
int a_y;
int a_z;

//int magnetom_x;
//int magnetom_y;
//int magnetom_z;
//float c_magnetom_x;
//float c_magnetom_y;
//float c_magnetom_z;
//float MAG_Heading;
float Accel_Vector[3] = {0, 0, 0};
float Gyro_Vector[3] = {0, 0, 0}; //Store the gyros turn rate in a vector
float Omega_Vector[3] = {0, 0, 0}; //Corrected Gyro_Vector data
float Omega_P[3] = {0, 0, 0}; //Omega Proportional correction
float Omega_I[3] = {0, 0, 0}; //Omega Integrator
float Omega[3] = {0, 0, 0};

// Euler angles
float roll;
float pitch;
float yaw;

float errorRollPitch[3] = {0, 0, 0};
float errorYaw[3] = {0, 0, 0};

unsigned int counter = 0;
byte gyro_sat = 0;

float DCM_Matrix[3][3] = {
  {
    1, 0, 0
  }
  , {
    0, 1, 0
  }
  , {
    0, 0, 1
  }
};
float Update_Matrix[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}; //Gyros here


float Temporary_Matrix[3][3] = {
  {
    0, 0, 0
  }
  , {
    0, 0, 0
  }
  , {
    0, 0, 0
  }
};

///////////////////////////////////////////////////////// End of IMU

byte s_data[LEN_DATA];

void setup() {
  Serial.begin(57600);
  I2C_Init();
  delay(1000);


//  SPI.setMOSI(SDCARD_MOSI_PIN);
//  SPI.setSCK(SDCARD_SCK_PIN);
//  if (!(SD.begin(SDCARD_CS_PIN))) {
//    // stop here, but print a message repetitively
//    while (1) {
//      Serial.println("Unable to access the SD card");
//      delay(500);
//    }
//  }


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  delay(1000);

  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  displayData01();

  delay(1000);

  Accel_Init();
  //  Compass_Init();
  Gyro_Init();
  delay(20);

  for (int i = 0; i < 32; i++) // We take some readings...
  {
    Read_Gyro();
    Read_Accel();
    for (int y = 0; y < 6; y++) // Cumulate values
      AN_OFFSET[y] += AN[y];
    delay(20);
  }
  for (int y = 0; y < 6; y++)
    AN_OFFSET[y] = AN_OFFSET[y] / 32;

  AN_OFFSET[5] -= GRAVITY * SENSOR_SIGN[5];

  Serial.println("Offset:");
  for (int y = 0; y < 6; y++)
    Serial.println(AN_OFFSET[y]);

  delay(2000);

  timer = millis();
  delay(20);
  counter = 0;

  for (int i = 0; i < LEN_DATA; i++) {
    s_data[i] = 0;
  }

  s_data[0] = 255;

}

void loop() {
//  getSesorData();

  sendSerialData();


}

void sendSerialData() {
  if (Serial.available() > 0) {

    char first_byte = Serial.read();

//    Serial.print("first_byte ="); Serial.println(first_byte);


    if (first_byte == 'A') {
      getSesorData();
      Serial.write(s_data, LEN_DATA);

    } else {
      Serial.clear();
      while (Serial.available()) {
        Serial.read();
      }
    }
  }
}

void getSesorData() {
  if ((millis() - timer) >= 100) // Main loop runs at 50Hz
  {
    counter++;
    timer_old = timer;
    timer = millis();
    if (timer > timer_old)
    {
      G_Dt = (timer - timer_old) / 1000.0; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
      if (G_Dt > 0.2)
        G_Dt = 0; // ignore integration times over 200 ms
    }
    else
      G_Dt = 0;



    // *** DCM algorithm
    // Data adquisition
    Read_Gyro();   // This read gyro data
    Read_Accel();     // Read I2C accelerometer

    if (counter > 5)  // Read compass data at 10Hz... (5 loop runs)
    {
      counter = 0;
      //        Read_Compass();    // Read I2C magnetometer
      //        Compass_Heading(); // Calculate magnetic heading
    }

    // Calculations...
    Matrix_update();
    Normalize();
    Drift_correction();
    Euler_angles();
    // ***
    s_data[0] = 255;

    s_data[1] = (gyro_x + 10000) / 256;
    s_data[2] = (gyro_x + 10000) % 256;
    s_data[3] = (gyro_y + 10000) / 256;
    s_data[4] = (gyro_y + 10000) % 256;
    s_data[5] = (gyro_z + 10000) / 256;
    s_data[6] = (gyro_z + 10000) % 256;

    s_data[7] = (accel_x + 10000) / 256;
    s_data[8] = (accel_x + 10000) % 256;
    s_data[9] = (accel_y + 10000) / 256;
    s_data[10] = (accel_y + 10000) % 256;
    s_data[11] = (accel_z + 10000) / 256;
    s_data[12] = (accel_z + 10000) % 256;

    s_data[13] = (AN[0] + 10000) / 256;
    s_data[14] = (AN[0] + 10000) % 256;
    s_data[15] = (AN[1] + 10000) / 256;
    s_data[16] = (AN[1] + 10000) % 256;
    s_data[17] = (AN[2] + 10000) / 256;
    s_data[18] = (AN[2] + 10000) % 256;

    s_data[19] = (AN[3] + 10000) / 256;
    s_data[20] = (AN[3] + 10000) % 256;
    s_data[21] = (AN[4] + 10000) / 256;
    s_data[22] = (AN[4] + 10000) % 256;
    s_data[23] = (AN[5] + 10000) / 256;
    s_data[24] = (AN[5] + 10000) % 256;

    byte check_sum = 0;

    for (int i = 1; i < LEN_DATA - 1; i++) {
      check_sum = check_sum + s_data[i];
    }

    check_sum = check_sum % 256;
    s_data[29] = check_sum;


//        Serial.print("gyro_x: ");
//        Serial.println(gyro_x);
//        Serial.print("gyro_y: ");
//        Serial.println(gyro_y);
//        Serial.print("gyro_z: ");
//        Serial.println(gyro_z);
//        Serial.println();
//        Serial.print("(AN[0]): ");
//        Serial.println((AN[0]));
//        Serial.print("(AN[1]): ");
//        Serial.println((AN[1]));
//        Serial.print("(AN[2]): ");
//        Serial.println((AN[2]));
//        Serial.println();
//        Serial.print("accel_x: ");
//        Serial.println(accel_x);
//        Serial.print("accel_y: ");
//        Serial.println(accel_y);
//        Serial.print("accel_z: ");
//        Serial.println(accel_z);
//        Serial.println();
//        Serial.print("(AN[3]): ");
//        Serial.println((AN[3]));
//        Serial.print("(AN[4]): ");
//        Serial.println((AN[4]));
//        Serial.print("(AN[5]): ");
//        Serial.println((AN[5]));
//        Serial.println();
    //    sensor_value = (AN[4]);
    //    if (sensor_value > 250)sensor_value = 250;
    //    sensor_value = 250 - sensor_value; // flip it to mount sensor on top
    //Serial.println((AN[4]));
    // printdata();
  }
}
