/*
/
/  Specifically for an arduino that operates at 5V logic levels, like the nano.
*/


#include <SPI.h>                        // library required for serial communication
#include <SD.h>                         // library required for microSD activities
#include <CircularBuffer.h>             // Easy Circular Arrays for moving averages


int scale = 1000;                       // Accelerometer range 3000 milli-g
int rate = 10;                          // How many samples per second to take (Hz)
CircularBuffer<int, 10> rawX, rawY, rawZ;   // Running buffers for raw accel readings
float SX, SY, SZ;                       // Scaled values for each axis
unsigned long time0 = 0;                // Initial time
unsigned long timeX = 0;                // Running time


void setup() {                       
  Serial.begin(9600);                   // Open serial communications and wait for port to open:
  while (!Serial){}                     // wait for serial port to connect.

  time0 = millis();  
}


void loop()  {                         
  rawX.push(analogRead(A2));             // Add current values of each axis to the buffer
  rawY.push(analogRead(A1));             // Converts input voltage from 0V-MaxV to int 0-1023
  rawZ.push(analogRead(A0));             //   but accelerometer only outputs 0-3.3V

  SX = map(averageBuff(rawX), 308, 442, -scale, scale);
  SY = map(averageBuff(rawY), 303, 418, -scale, scale);
  SZ = map(averageBuff(rawZ), 305, 428, -scale, scale);

  timeX = millis();

  // Print out accelerometer readings
  Serial.print("Time: ");Serial.print(timeX-time0);Serial.print(" ");
  Serial.print("  SX: ");Serial.print(SX);Serial.print(" ");
  Serial.print("  SY: ");Serial.print(SY);Serial.print(" ");
  Serial.print("  SZ: ");Serial.print(SZ);Serial.print(" ");
  Serial.print("   g: ");Serial.println(sqrt(SX*SX+SY*SY+SZ*SZ));


  
  delay(1000/rate);
}


// Get the average value of a circular buffer
float averageBuff(CircularBuffer<int, 10> &myBuffer) {
  float len = myBuffer.size();
  float sum = 0;
  float avg;

  for (byte ii=0; ii<len; ii++) {
    sum += myBuffer[ii];
  }
  avg = sum / len;

  return avg;
}
