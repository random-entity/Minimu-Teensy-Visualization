

    // // ***
    // s_data[0] = 255;

    // s_data[1] = (gyro_x + 10000) / 256;
    // s_data[2] = (gyro_x + 10000) % 256;
    // s_data[3] = (gyro_y + 10000) / 256;
    // s_data[4] = (gyro_y + 10000) % 256;
    // s_data[5] = (gyro_z + 10000) / 256;
    // s_data[6] = (gyro_z + 10000) % 256;

    // s_data[7] = (accel_x + 10000) / 256;
    // s_data[8] = (accel_x + 10000) % 256;
    // s_data[9] = (accel_y + 10000) / 256;
    // s_data[10] = (accel_y + 10000) % 256;
    // s_data[11] = (accel_z + 10000) / 256;
    // s_data[12] = (accel_z + 10000) % 256;

    // s_data[13] = (AN[0] + 10000) / 256;
    // s_data[14] = (AN[0] + 10000) % 256;
    // s_data[15] = (AN[1] + 10000) / 256;
    // s_data[16] = (AN[1] + 10000) % 256;
    // s_data[17] = (AN[2] + 10000) / 256;
    // s_data[18] = (AN[2] + 10000) % 256;

    // s_data[19] = (AN[3] + 10000) / 256;
    // s_data[20] = (AN[3] + 10000) % 256;
    // s_data[21] = (AN[4] + 10000) / 256;
    // s_data[22] = (AN[4] + 10000) % 256;
    // s_data[23] = (AN[5] + 10000) / 256;
    // s_data[24] = (AN[5] + 10000) % 256;

    // byte check_sum = 0;

    // for (int i = 1; i < LEN_DATA - 1; i++)
    // {
    //   check_sum = check_sum + s_data[i];
    // }

    // check_sum = check_sum % 256;
    // s_data[29] = check_sum;

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
