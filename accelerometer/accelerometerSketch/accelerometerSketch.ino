#include <SPI.h>                                  // library required for serial communication
#include <SD.h>                                   // library required for microSD activities


File Data;                                        // declaration for the data file as Data
int scale = 1000;                                 // accelerometer range  expressed as +/- 1000 milli-g
int rate = 10;                                    // How many samples per second to take (Hz)
int rawX, rawY, rawZ;                             // Variables for the 3 axis analog reads
float SX, SY, SZ;                                 // Scaled values for each axis


void setup() {
  Serial.begin(9600);                             // Open serial communications and wait for port to open:
  while (!Serial){                                // wait for serial port to connect.
  }
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    Serial.println("Restart to try again.");
    while (1);
  }
  Serial.println("initialization done.");
 
  Data = SD.open("Accel.csv", FILE_WRITE);        // defines Accel.csv as name of data file

  if (Data) {
    Data.println("SX [milli-g], SY [milli-g], SZ [milli-g], g");   // header for all subsequent data
    Data.close();                                 // close the file:
  } else {
    Serial.println("Error opening File");         // error message if the file did not open
  }
}


void loop() {
  Data = SD.open("Accel.csv", FILE_WRITE);        // opens data file ‘Accel.txt’
  rawX = analogRead(A0);                          // Raw accelerometer data for each axis
  rawY = analogRead(A1);
  rawZ = analogRead(A2);
 
  SX = map(rawX, 273, 410, -scale, scale);      // the measured values 298, 411, will be different for
  SY = map(rawY, 268, 408, -scale, scale);      // each sensor.
  SZ = map(rawZ, 281, 418, -scale, scale);
  
  // Print out raw X,Y,Z accelerometer readings as well as total acceleration vector
  Data.print(SX); Data.print(", ");
  Data.print(SY); Data.print(", ");
  Data.print(SZ); Data.print(", ");
  Data.println(sqrt(SX*SX+SY*SY+SZ*SZ)/scale);
  Data.close();                                   // closes file, saves data after each writing cycle
  delay(1000/rate);
}
