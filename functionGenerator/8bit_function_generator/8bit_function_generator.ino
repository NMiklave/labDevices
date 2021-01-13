/* 8 Bit R2R Ladder DAC and Function Generator
 * Nicholas Miklave
 * Last Modified: 12/8/2020
 * 
 * This script runs an 8 bit R2R ladder function generator. The digital
 *    pins D2 through D9 (LSB and MSB respectively) access the rungs of
 *    the R2R ladder, which will output over the range of 0 to 5 Volts.
 *    
 * For practical reasons, this output is then fed into a voltage
 *    divider, which cuts that in approximately 1/5th for an actual
 *    range of 0-1 V. This also allows the 5V line from the nano to 
 *    power a LT1797 Op-Amp which buffers the ladder and divider from
 *    a low pass filter, which itself is again buffered from the 
 *    generator final output.
 *
 * 
 * Bits from least to most significance: a0 --> a7
 * 
 * Example:   # | a2 | a1 | a0
 *            0 |  0 |  0 |  0
 *            1 |  0 |  0 |  1
 *            2 |  0 |  1 |  0
 *            3 |  0 |  1 |  1
 *            4 |  1 |  0 |  0
 *            5 |  1 |  0 |  1
 *            6 |  1 |  1 |  0
 *            7 |  1 |  1 |  1
 *
 * Wave selects the type of wave to output.
 *    0 = Sinusoidal (default)
 *    1 = Increasing Sawtooth
 *    2 = Decreasing Sawtooth
 *    3 = 50% Duty Cycle Square
 *    4 = Triangle
 *    
 *    Additional waveforms can be added as needed in the void function
 *    "createWaveforms" 
 */
 
int wave = 4;

// Output pins
int a0 = 2;  // LSB
int a1 = 3;
int a2 = 4;
int a3 = 5; 
int a4 = 6;
int a5 = 7; 
int a6 = 8;
int a7 = 9; // MSB

const int res = pow(2, 8);    // Resolution of an 8 bit system
int waveform[res];  //  Accessed variable for outputting presets



void createWaveforms() {
  // Populate the preset waveforms with data

  switch (wave) {
    case 1:       // Rising Sawtooth Wave
      for (int ii=0; ii<res; ++ii) waveform[ii] = ii;  
      break;
    case 2:       // Falling Sawtooth Wave
      for (int ii=0; ii<res; ++ii) waveform[ii]=255-ii;
      break;
    case 3:       // 50% Duty Cycle Square Wave
      for (int ii=0; ii<res; ++ii) {
        if (ii<127) waveform[ii] = 0;
        else waveform[ii] = 255;
        }
      break;
    case 4:       // Triangle Wave
      for (int ii=0; ii<res; ++ii) {
        if (ii<128) waveform[ii] = 2*ii;
        else waveform[ii] = 256 - 2*(ii-128);
        }      
      break;
    default:      // Sinusoidal Wave
      for (int ii=0; ii<res; ++ii) {
        waveform[ii] = round(127.5 - 127.5*cos(2*PI*ii/256));
        }
      break;
  }

//  for (int ii=0; ii<res; ++ii) Serial.println(waveform[ii]);
}



void setup() {
  // Open serial monitor at 9600 baud
  Serial.begin(9600);

  // Set pinmodes for output
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(a4, OUTPUT);
  pinMode(a5, OUTPUT);
  pinMode(a6, OUTPUT);
  pinMode(a7, OUTPUT);

  // Create and Select Waveforms
  createWaveforms();
}



void loop() {
  for (int ii = 0; ii < res; ++ii) {  
    // Check digit value 
//    Serial.print(waveform[ii]);
//    Serial.print("  ");
//    Serial.println(waveform[ii], BIN);

    // Set pin outputs by binary number
    digitalWrite(a7, HIGH && (waveform[ii] & B10000000));
    digitalWrite(a6, HIGH && (waveform[ii] & B01000000));
    digitalWrite(a5, HIGH && (waveform[ii] & B00100000));
    digitalWrite(a4, HIGH && (waveform[ii] & B00010000));
    digitalWrite(a3, HIGH && (waveform[ii] & B00001000));
    digitalWrite(a2, HIGH && (waveform[ii] & B00000100));
    digitalWrite(a1, HIGH && (waveform[ii] & B00000010));
    digitalWrite(a0, HIGH && (waveform[ii] & B00000001));

    delay(.5);
  }
}
