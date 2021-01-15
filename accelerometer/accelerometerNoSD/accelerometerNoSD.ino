#include <SPI.h>                        // library required for serial communication
#include <SD.h>                         // library required for microSD activities


int scale = 3000;                          // Accelerometer range 3000 milli-g
int rate = 2;                           // How many samples per second to take (Hz)
int rawX, rawY, rawZ;
float SX, SY, SZ;                       // Scaled values for each axis
boolean micro_is_5V = true;


void setup() {                        

  Serial.begin(9600);                   // Open serial communications and wait for port to open:
  while (!Serial){}                     // wait for serial port to connect.
  Serial.println("Preparing to Print to Console...");
  
  // pinMode(10, OUTPUT);
  // digitalWrite(10, HIGH);            //requirement for Arduino logic; value may be 4 for some boards
  
}


void loop()  {                         

  rawX = analogRead(A0);                // Raw accelerometer data for each axis
  rawY = analogRead(A1);                // Converts input voltage from 0V-MaxV to int 0-1023
  rawZ = analogRead(A2);                //   but accelerometer only outputs 0-3.3V

  if (micro_is_5V) {                    // microcontroller runs @ 5V
    SX = map(rawX, 0, 675, -scale, scale);  // Accel only outputs up to 3.3V, so board reads max binary
    SY = map(rawY, 0, 675, -scale, scale);  //   of (3.3/5) * 1023 = 675.18 --> 675
    SZ = map(rawZ, 281, 418, -1000, 1000); 
  } else {                              // microcontroller runs @ 3.3V
    SX = map(rawX, 0, 1023, -scale, scale); // Reading 3.3V on analog pin outputs binary 1023
    SY = map(rawY, 0, 1023, -scale, scale);
    SZ = map(rawZ, 0, 1023, -scale, scale);
  }

//  // Print out raw X,Y,Z accelerometer readings
//  Serial.print("X:  "); Serial.print(SX); Serial.print("   ");
//  Serial.print("Y:  "); Serial.print(SY); Serial.print("   ");
//  Serial.print("Z:  "); Serial.print(SZ); Serial.print("   ");Serial.print("");
//  Serial.print("Net g:  "); Serial.println(sqrt(SX*SX+SY*SY+SZ*SZ)/1000);

  Serial.print("rawZ:  ");Serial.print(rawZ);Serial.print("   ");
  Serial.print("SZ:    ");Serial.print(SZ);Serial.println("");
  
  delay(1000/rate);
}
