#include <SPI.h>                                  // library required for serial communication
#include <SD.h>                                   // library required for microSD activities


File Data;                                        // declaration for the data file as Data
int scale = 1000;                                 // accelerometer range  expressed as +/- 1000 milli-g
float SX, SY, SZ;                                 // Scaled values for each axis
boolean micro_is_5V = true;


void setup() {                                    // define conditions and parameters
  Serial.begin(9600);                             // Open serial communications and wait for port to open:
  while (!Serial){                                // wait for serial port to connect.
  }
  Serial.print("Initializing SD card...");
  
  // pinMode(10, OUTPUT);
  // digitalWrite(10, HIGH);                      //requirement for Arduino logic; value may be 4 for some boards
  
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }

  Serial.println("Initialization done.");
  Data = SD.open("Accel.txt", FILE_WRITE);        // defines Accel.txt as name of data file

  if (Data) {
    Serial.print("Header Accel");
    Data.println("Data are listed as x, y, z");   // header for all subsequent data
    Data.close();                                 // close the file:
  } else {
    Serial.println("Error opening File");         // error message if the file did not open
  }
}


void loop()  {                                    // loop runs indefinitely

  Data = SD.open("Accel.txt", FILE_WRITE);        // opens data file ‘Accel.txt’
  int rawX = analogRead(A0);                      // Raw accelerometer data for each axis
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);

  if (micro_is_5V)  {                             // microcontroller runs @ 5V
    SX = map(rawX, 298, 411, -scale, scale);      // the measured values 298, 411, will be different for
    SY = map(rawY, 296, 409, -scale, scale);      // each sensor.
    SZ = map(rawZ, 296, 430, -scale, scale);
  } else {                                        // microcontroller runs @ 3.3V
    SX = map(rawX, 0, 1023, -scale, scale);
    SY = map(rawY, 0, 1023, -scale, scale);
    SZ = map(rawZ, 0, 1023, -scale, scale);
  }

                                                  // Print out raw X,Y,Z accelerometer readings
  Data.print("X:  "); Data.print(SX); Data.print("   ");
  Data.print("Y:  "); Data.print(SY); Data.print("   ");
  Data.print("Z:  "); Data.print(SZ); Data.print("   ");
  Data.print("Net g:  "); Data.println(sqrt(SX*SX+SY*SY+SZ*SZ)/scale);
  Data.close();                                   // closes file, saves data after each writing cycle
  delay(500);                                     // 500 milliseconds = 2 Hz sampling frequency

}
