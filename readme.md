## 개요 | Introduction
서울오픈미디어에서 개발하는 MinIMU 센서와 MicroMod Teensy 마이크로프로세서 등이 임베디드된 GLPS 헤드폰의 MinIMU 센서 데이터를 PC 디스플레이 상에서 시각화할 수 있도록 하기 위한 Teensyduino와 Processing 코드들입니다.

This repo contains Teensyduino and Processing codes which serve the purpose of visualizing on PC monitor the sensor data captured by a MinIMU sensor embedded in custom made GLPS headphones that have been developed by Seoul Open Media. Embedded on the headphones other than the MinIMU are the MicroMod Teensy microprocessor, LPS module and more.

## 폴더 구조 | Directories
- /libs
  - Teensy에 필요한 외부 라이브러리들 (수정 있음) 백업
  - The backup of (modified) external libraries used for the Teensy
- /tdino
  - Teensyduino 코드, 센서 데이터를 시리얼로 출력하기 위한
  - Teensyduino codes, for writing sensor data on serial
- /proc
  - 프로세싱 코드, 시리얼에서 읽어온 센서 데이터 시각화를 위한
  - Processing codes, for visualizing sensor data read from serial
- /ref
  - 참고자료 & 퍼온 라이브러리 원본 .zip 등
  - References & external libraries' backup .zip files

## 개발 환경 | Development Environment

- 서울오픈미디어에서 개발한 GLPS 헤드폰 (3세대)에서 테스트 되었습니다.
- 사용되는 프로세서와 센서는 다음과 같습니다.

- We are working with Seoul Open Media's GLPS Headphones (3rd Generation)
- The processors and sensors used are:

  - SparkFun MicroMod Teensy 
    - [SparkFun](https://www.sparkfun.com/products/16402)
  - Pololu MinIMU-9 MinIMU-9 v5 Gyro, Accelerometer, and Compass (LSM6DS33 and LIS3MDL Carrier)
    - [Pololu](https://www.pololu.com/product/2738)

- MinIMU 센서와 MicroMod Teensy는 I2C 방식으로 연결되어 소통하고 있습니다.
- The MinIMU and the MicroMod Teensy are communicating by I2C.

## 사용법 | How to use
- /libs 안에 있는 라이브러리들을 아두이노 라이브러리 폴더에 복사해야 합니다.
- /tdino/headphone-minimu.ino를 Teensyduino로 열어 Teensy로 업로드합니다.
- Processing의 grafica 라이브러리가 설치되어 있지 않다면 설치합니다. 
  - Processing IDE 내에서 할 수 있습니다.
    - 스케치 > 내부 라이브러리 > 라이브러리 추가하기 > grafica 검색
- /proc/serial_data_plotting/serial_data_plotting.pde를 Processing IDE로 열어 실행시킵니다.

- Copy the contents of /libs to your Arduino Library folder.
- Open /tdino/headphone-minimu.ino with Teensyduino and upload to Teesy.
- On the Processing side you need the "grafica" library.
  - You can install it inside the Processing IDE.
    - Sketch > Import Library > Add Library > search "grafica"
- Open /proc/serial_data_plotting/serial_data_plotting.pde with the Processing IDE and run.