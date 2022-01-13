## Introduction
This repo contains Teensyduino and Processing codes which serve the purpose of visualizing on PC monitor the sensor data captured by a MinIMU sensor embedded in custom made GLPS headphones that have been developed by Seoul Open Media. Embedded on the headphones other than the MinIMU are the MicroMod Teensy microprocessor, LPS module and more.

## Directories
- ```/libs```
  - The backup of (modified) external libraries used for the Teensy
- ```/teensy```
  - Teensyduino codes, for writing sensor data on serial
- ```/proc```
  - Processing codes, for visualizing sensor data read from serial
- ```/ref```
  - References & external libraries' backup .zip files

## Development Environment
- We are working with Seoul Open Media's GLPS Headphones (3rd Generation)
- The processors and sensors used are:

  - SparkFun MicroMod Teensy 
    - [SparkFun](https://www.sparkfun.com/products/16402)
  - Pololu MinIMU-9 MinIMU-9 v5 Gyro, Accelerometer, and Compass (LSM6DS33 and LIS3MDL Carrier)
    - [Pololu](https://www.pololu.com/product/2738)

- The MinIMU and the MicroMod Teensy are communicating by I2C.

## How to use
- Copy the contents of ```/libs``` to your Arduino Library folder.
- Open ```/teensy/headphone-minimu.ino``` with Teensyduino and upload to Teesy.
- On the Processing side you need the "grafica" library.
  - You can install it inside the Processing IDE.
    - Sketch > Import Library > Add Library > search "grafica"
- Open ```/proc/minimu_data_plotter/minimu_data_plotter.pde``` with the Processing IDE and run.

## How it works
### On the Teensy side
- In ```/teensy/headphone-minimu.ino``` we can see:
```
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
```
- This is the function that encodes and writes data to the serial port.
- This function is called whenever Teensy reads an ```'A'``` on its serial input.
  - ```s_data_2byte``` is a two-dimensional array of type ```byte```
    - ```byte s_data_2byte[14][2];``` (line 109)
  - for each ```i = 0 ~ 13```, ```s_data_2byte[i]``` is a ```byte``` array of length 2.
  - ```Serial.write(s_data_2byte[i], 2);``` (line 209) writes the two ```byte``` elements of ```s_data_2byte[i]``` to the serial port.

- What are the elements of ```s_data_2byte[i]```?
  - Refer to the ```ShortTo2Bytes``` function in ```/teensy/conversions.ino```
  - ```
    void ShortTo2Bytes(short n, byte *arr)
    {
        *arr = (n >> 8) & 0xFF;
        *(arr + 1) = n & 0xFF;
    }
    ```
    - ```ShortTo2Bytes(short n, byte *arr)``` breaks ```short n``` to two pieces of ```byte``` and assigns those bytes to the two elements of ```arr```.
    - ```arr[0]``` is set to the higher binary decimals (```n >> 8```),
    - and ```arr[1]``` is set to the lower binary decimals (```n & 0xFF```)
      - The order is important, because we need to know when decoding how the data was encoded.
  - We are encoding ```int```s 
    - ```gyro_x```, ```gyro_y```, ```gyro_z``` 
      - into ```s_data_2byte[0]```, ```s_data_2byte[1]```, ```s_data_2byte[2]```,
    - ```accel_x```, ```accel_y```, ```accel_z``` 
      - into ```s_data_2byte[3]```, ```s_data_2byte[4]```, ```s_data_2byte[5]```,
    - ```AN[0 ~ 6]``` to ```s_data_2byte[6 ~ 12]```.
  - The first and the last element of ```s_data_2byte``` are used to write a start signal and a check-sum signal, respectively.
    - ```s_data_2byte[0]``` is ```{ 0x7F, 0xFF }```, which is the positive maximum ```short```.
    - ```s_data_2byte[13]``` is the sum of ```TwoBytesToShort(s_data_2byte[1 ~ 12])``` which are the un-encoded value of ```s_data_2byte[1 ~ 12]``` (i.e. ```gyro_xyz```, ```accel_xyz```, ```AN[1~6]```), encoded to two bytes.
- What are ```gyro_xyz```, ```accel_xyz```, and ```AN[1~6]```?
  - These are the global variables values of which are set by ```getSensorData()```, which contains functions ```Read_Gyro()```, ```Read_Accel()```, ```Matrix_update()```, ```Normalize()```, ```Drift_correction()```, and ```Euler_angles()```, which came from the [pololu/minimu-9-ahrs-arduino public repository](https://github.com/pololu/minimu-9-ahrs-arduino/tree/master/MinIMU9AHRS).
    - I do not know how these sensor-related functions work...

### On the Processing side
- In ```/proc/minimu_data_plotter/minimu_data_plotter.pde``` we have:
```
void serialEvent(Serial s) {
  println("serial event : time = " + getStepTimeInSec() + " (sec)");
  serialToChannels(s);
}
```
```
void serialToChannels(Serial s) {
  s.readBytes(currentBuffer);
  byteBuffer = ByteBuffer.wrap(currentBuffer).order(ByteOrder.BIG_ENDIAN);
  for (int i = 0; i < channels.length; i++) {
    channels[i].add(byteBuffer.getShort());
  }
}
```
