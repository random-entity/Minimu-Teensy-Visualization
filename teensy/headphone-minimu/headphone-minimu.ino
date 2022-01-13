#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define VERSION 0.32
#define SOFT_VERSION 1
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
#define GRAVITY 256 //this equivalent to 1G in the raw data coming from the accelerometer

#define ToRad(x) ((x)*0.01745329252) // *pi/180
#define ToDeg(x) ((x)*57.2957795131) // *180/pi

// gyro: 2000 dps full scale
// 70 mdps/digit; 1 dps = 0.07
#define Gyro_Gain_X 0.07                          //X axis Gyro gain
#define Gyro_Gain_Y 0.07                          //Y axis Gyro gain
#define Gyro_Gain_Z 0.07                          //Z axis Gyro gain
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

float G_Dt = 0.02; // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer = 0; //general purpuse timer
long timer_old;
int AN[6];                             //array that stores the gyro and accelerometer data
int AN_OFFSET[6] = {0, 0, 0, 0, 0, 0}; //Array that stores the Offset of the sensors

int gyro_x;
int gyro_y;
int gyro_z;
int accel_x;
int accel_y;
int accel_z;

float Accel_Vector[3] = {0, 0, 0};
float Gyro_Vector[3] = {0, 0, 0};  //Store the gyros turn rate in a vector
float Omega_Vector[3] = {0, 0, 0}; //Corrected Gyro_Vector data
float Omega_P[3] = {0, 0, 0};      //Omega Proportional correction
float Omega_I[3] = {0, 0, 0};      //Omega Integrator
float Omega[3] = {0, 0, 0};

// Euler angles
float roll;
float pitch;
float yaw;

float errorRollPitch[3] = {0, 0, 0};
float errorYaw[3] = {0, 0, 0};

byte gyro_sat = 0;

float DCM_Matrix[3][3] = {
  {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
};

float Update_Matrix[3][3] = {
  {0, 1, 2}, {3, 4, 5}, {6, 7, 8}
}; //Gyros here

float Temporary_Matrix[3][3] = {
  {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};

///////////////////////////////////////////////////////// End of IMU

byte s_data_2byte[14][2];

void setup()
{
  Serial.begin(57600);
  I2C_Init();
  delay(1000);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  delay(1000);

  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);                 // Use full 256 char 'Code Page 437' font
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

  //  Serial.println("Offset:");
  //  for (int y = 0; y < 6; y++) {
  //    Serial.println(AN_OFFSET[y]);
  //  }

  delay(2000);

  timer = millis();
  delay(20);
}

void loop()
{
  getSensorData();

  if (Serial.available() > 0) {
    if (Serial.read() == 'A') {
      sendSerialData();
    } else {
      Serial.clear();
      while (Serial.available())
      {
        Serial.read();
      }
    }
  }
}

void sendSerialData()
{
  s_data_2byte[0][0] = 0x7F;
  s_data_2byte[0][1] = 0xFF;

  ShortTo2Bytes(gyro_x, s_data_2byte[1]);
  ShortTo2Bytes(gyro_y, s_data_2byte[2]);
  ShortTo2Bytes(gyro_z, s_data_2byte[3]);

  ShortTo2Bytes(accel_x, s_data_2byte[4]);
  ShortTo2Bytes(accel_y, s_data_2byte[5]);
  ShortTo2Bytes(accel_z, s_data_2byte[6]);

  ShortTo2Bytes(AN[0], s_data_2byte[7]);
  ShortTo2Bytes(AN[1], s_data_2byte[8]);
  ShortTo2Bytes(AN[2], s_data_2byte[9]);
  ShortTo2Bytes(AN[3], s_data_2byte[10]);
  ShortTo2Bytes(AN[4], s_data_2byte[11]);
  ShortTo2Bytes(AN[5], s_data_2byte[12]);

  short check_sum = 0;

  for (int i = 1; i <= 12; i++) {
    check_sum += TwoBytesToShort(s_data_2byte[i]);
  }

  ShortTo2Bytes(check_sum, s_data_2byte[13]);

  for (int i = 0; i < 14; i++)
  {
    Serial.write(s_data_2byte[i], 2);
  }
}

void getSensorData()
{
  if ((millis() - timer) >= 100) // Main loop runs at 50Hz
  {
    timer_old = timer;
    timer = millis();
    if (timer > timer_old)
    {
      G_Dt = (timer - timer_old) / 1000.0; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
      if (G_Dt > 0.2)
        G_Dt = 0; // ignore integration times over 200 ms
    }
    else
    {
      G_Dt = 0;
    }

    // *** DCM algorithm
    // Data adquisition
    Read_Gyro();  // This read gyro data
    Read_Accel(); // Read I2C accelerometer

    // Calculations...
    Matrix_update();
    Normalize();
    Drift_correction();
    Euler_angles();
  }
}
