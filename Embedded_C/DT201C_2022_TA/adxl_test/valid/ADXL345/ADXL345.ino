#include <Wire.h>
// Registers for ADXL345
#define ADXL345_ADDRESS (0xA6 >> 1)  // address for device is 8 bit but shift to the
// right by 1 bit to make it 7 bit because the
// wire library only takes in 7 bit addresses
#define ADXL345_REGISTER_XLSB (0x32)

int accelerometer_data[3];
// void because this only tells the cip to send data to its output register
// writes data to the slave's buffer
void i2c_write(int address, byte reg, byte data) {

  // Send output register address
  Wire.beginTransmission(address);
  // Connect to device
  Wire.write(reg);
  // Send data
  Wire.write(data); //low byte
  Wire.endTransmission();
}

// void because using pointers
// microcontroller reads data from the sensor's input register
void i2c_read(int address, byte reg, int count, byte* data) {
  // Used to read the number of data received
  int i = 0;
  // Send input register address
  Wire.beginTransmission(address);
  // Connect to device
  Wire.write(reg);
  Wire.endTransmission();

  // Connect to device
  Wire.beginTransmission(address);
  // Request data from slave
  // Count stands for number of bytes to request
  Wire.requestFrom(address, count);
  while (Wire.available()) // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    data[i] = c;
    i++;
  }
  Wire.endTransmission();
}

void init_adxl345() {
  byte data = 0;

  i2c_write(ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
  i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);   // Power register


  i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);   // x
  i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);   // Y
  i2c_write(ADXL345_ADDRESS, 0x20, 0x05);   // Z

  // Check to see if it worked!
  i2c_read(ADXL345_ADDRESS, 0X00, 1, &data);
  if (data == 0xE5)
    Serial.println("it work Success");
  else
    Serial.println("it work Fail");
}

void read_adxl345() {
  byte bytes[6];
  memset(bytes, 0, 6);

  // Read 6 bytes from the ADXL345
  i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
  // Unpack data
  for (int i = 0; i < 3; ++i) {
    accelerometer_data[i] = (int)bytes[2 * i] + (((int)bytes[2 * i + 1]) << 8);
  }
}
// initialise and start everything
void setup() {
  pinMode(7, INPUT);
  digitalWrite(7, HIGH);

  Wire.begin();
  Serial.begin(9600);
  for (int i = 0; i < 3; ++i) {
    accelerometer_data[i]  = 0;
  }
  init_adxl345();
}

#define REAL 1
float data0;
float data1;
float data2;

void loop() {
  while (digitalRead(7) == HIGH) {
    ;
  }
  delay(1000);
  data0 = 0;
  data1 = 0;
  data2 = 0;
  /* n = 1 */
  for (int i = 0; i < 100; i++) {
    read_adxl345();
    Serial.print(accelerometer_data[0]);
    Serial.print(",");
    Serial.print(accelerometer_data[1] - 260);

    Serial.print(",");
    Serial.print(accelerometer_data[2] - 20);
    Serial.print("\n");
  }

  Serial.println("NEXT");

  /* n = 25 */
  for (int i = 0; i < 100; i++) {
    data0 = 0;
    data1 = 0;
    data2 = 0;

    for (int j = 0; j < 25; j++) {
      read_adxl345();
      data0 += accelerometer_data[0];
      data1 += accelerometer_data[1] - 260;
      data2 += accelerometer_data[2] - 20;
    }

    data0 /= 25;
    data1 /= 25;
    data2 /= 25;

    Serial.print((String)data0);
    Serial.print(",");
    Serial.print((String)data1);

    Serial.print(",");
    Serial.print((String)data2);
    Serial.print("\n");
  }

  Serial.println("NEXT");

  /* n = 50 */
  for (int i = 0; i < 100; i++) {
    data0 = 0;
    data1 = 0;
    data2 = 0;
    for (int j = 0; j < 50; j++) {
      read_adxl345();
      data0 += accelerometer_data[0];
      data1 += accelerometer_data[1] - 260;
      data2 += accelerometer_data[2] - 20;
    }

    data0 /= 50;
    data1 /= 50;
    data2 /= 50;

    Serial.print((String)data0);
    Serial.print(",");
    Serial.print((String)data1);

    Serial.print(",");
    Serial.print((String)data2);
    Serial.print("\n");
  }

  Serial.println("NEXT");

  /* n = 75 */
  for (int i = 0; i < 100; i++) {
    data0 = 0;
    data1 = 0;
    data2 = 0;
    for (int j = 0; j < 75; j++) {
      read_adxl345();
      data0 += accelerometer_data[0];
      data1 += accelerometer_data[1] - 260;
      data2 += accelerometer_data[2] - 20;
    }

    data0 /= 75;
    data1 /= 75;
    data2 /= 75;

    Serial.print((String)data0);
    Serial.print(",");
    Serial.print((String)data1);

    Serial.print(",");
    Serial.print((String)data2);
    Serial.print("\n");
  }

  Serial.println("NEXT");

  /* n = 100 */
  for (int i = 0; i < 100; i++) {
    data0 = 0;
    data1 = 0;
    data2 = 0;
    for (int j = 0; j < 100; j++) {
      read_adxl345();
      data0 += accelerometer_data[0];
      data1 += accelerometer_data[1] - 260;
      data2 += accelerometer_data[2] - 20;
    }

    data0 /= 100;
    data1 /= 100;
    data2 /= 100;

    Serial.print((String)data0);
    Serial.print(",");
    Serial.print((String)data1);

    Serial.print(",");
    Serial.print((String)data2);
    Serial.print("\n");
  }




  Serial.println("DONE");

  while (1) {
    ;
  }

























}
