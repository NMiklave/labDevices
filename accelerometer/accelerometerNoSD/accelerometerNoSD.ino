/*

 Specifically for an arduino that operates at 5V logic levels, like the nano.
*/


#include <SPI.h>                        // library required for serial communication
#include <SD.h>                         // library required for microSD activities


int scale = 1000;                       // Accelerometer range 3000 milli-g
int rate = 20;                           // How many samples per second to take (Hz)
int rawX, rawY, rawZ;
float SX, SY, SZ;                       // Scaled values for each axis


void setup() {                        

  Serial.begin(9600);                   // Open serial communications and wait for port to open:
  while (!Serial){}                     // wait for serial port to connect.
  
  // pinMode(10, OUTPUT);
  // digitalWrite(10, HIGH);            //requirement for Arduino logic; value may be 4 for some boards
  
}


void loop()  {                         

  rawX = analogRead(A0);                // Raw accelerometer data for each axis
  rawY = analogRead(A1);                // Converts input voltage from 0V-MaxV to int 0-1023
  rawZ = analogRead(A2);                //   but accelerometer only outputs 0-3.3V

  SX = map(rawX, 273, 410, -scale, scale);
  SY = map(rawY, 268, 408, -scale, scale);
  SZ = map(rawZ, 281, 418, -scale, scale);

  // Print out raw X,Y,Z accelerometer readings
  Serial.print("SX:  ");Serial.print(SX);Serial.print("   ");
  Serial.print("SY:  ");Serial.print(SY);Serial.print("   ");
  Serial.print("SZ:  ");Serial.print(SZ);Serial.print("   ");
  Serial.print(" g:  ");Serial.println(sqrt(SX*SX+SY*SY+SZ*SZ));
  
  delay(1000/rate);
}
