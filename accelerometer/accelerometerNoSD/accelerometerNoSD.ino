#include <SPI.h>                        // library required for serial communication
#include <SD.h>                         // library required for microSD activities


File Data;                              // declaration for the data file as Data
int scale = 1000;                       // accelerometer range  expressed as +/- 1000 milli-g
int rate = 2;                           // How many samples per second to take (Hz)
int rawX, rawY, rawZ;
float SX, SY, SZ;                       // Scaled values for each axis
boolean micro_is_5V = true;


void setup() {                          // define conditions and parameters
  Serial.begin(9600);                   // Open serial communications and wait for port to open:
  while (!Serial){                      // wait for serial port to connect.
  }
  Serial.print("Preparing to Print to Console...");
  
  // pinMode(10, OUTPUT);
  // digitalWrite(10, HIGH);            //requirement for Arduino logic; value may be 4 for some boards
  
}


void loop()  {                          // loop runs indefinitely

  rawX = analogRead(A0);                // Raw accelerometer data for each axis
  rawY = analogRead(A1);
  rawZ = analogRead(A2);

  if (micro_is_5V)  {                   // microcontroller runs @ 5V
    SX = map(rawX, 298, 411, -scale, scale);  // the measured values 298, 411, will be different for
    SY = map(rawY, 296, 409, -scale, scale);  // each sensor.
    SZ = map(rawZ, 296, 430, -scale, scale);
  } else {                                    // microcontroller runs @ 3.3V
    SX = map(rawX, 0, 1023, -scale, scale);
    SY = map(rawY, 0, 1023, -scale, scale);
    SZ = map(rawZ, 0, 1023, -scale, scale);
  }

                                        // Print out raw X,Y,Z accelerometer readings
  Serial.print("X:  "); Serial.print(SX); Serial.print("   ");
  Serial.print("Y:  "); Serial.print(SY); Serial.print("   ");
  Serial.print("Z:  "); Serial.print(SZ); Serial.print("   ");
  Serial.print("Net g:  "); Serial.println(sqrt(SX*SX+SY*SY+SZ*SZ)/scale);
  
  delay(rate);
}
