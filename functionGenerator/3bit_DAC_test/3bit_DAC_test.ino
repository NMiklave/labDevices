/* 3 Bit R2R Ladder Digital-Analog Conversion Test
 * Nicholas Miklave
 * Last Modified: 12/6/2020
 * 
 * This script is to test the voltage output of a 3 bit R2R ladder. The
 * delay time can be adjusted to change the equivalent frequency. Actual
 * frequency is given by:
 * 
 *                f = 1 / ((cycles / 16e6) + (delay * 2^N));
 *                N = number of bits in ladder
 *            delay = delay time at end of loop
 *           cycles = number of clock cycles for a single void loop
 * 
 * Bits from least to most significance: a0 --> a2
 * 
 *        # | a2 | a1 | a0
 *        0 |  0 |  0 |  0
 *        1 |  0 |  0 |  1
 *        2 |  0 |  1 |  0
 *        3 |  0 |  1 |  1
 *        4 |  1 |  0 |  0
 *        5 |  1 |  0 |  1
 *        6 |  1 |  1 |  0
 *        7 |  1 |  1 |  1
 *
 * Wave selects the type of wave to output.
 *    0 = Sinusoidal (default)
 *    1 = Increasing Sawtooth
 *    2 = Decreasing Sawtooth
 *    3 = 50% Duty Cycle Square
 */
int wave = 1;

// Output pins
int a0 = 2;  // LSB
int a1 = 3;
int a2 = 4;  // MSB

const int res = pow(2, 3);    // Resolution of a 3 bit system
// Preset waveforms
int sineWave[res] = {0, 2, 5, 7, 7, 5, 2, 0};
int risingSaw[res] = {0, 1, 2, 3, 4, 5, 6, 7};
int fallingSaw[res] = {7, 6, 5, 4, 3, 2, 1, 0};
int squareWave[res] = {0, 0, 0, 0, 7, 7, 7, 7};

int waveform[res];  //  Accessed variable for outputting presets



void pickWaveform() {
  // Call this to select a waveform based on the selected type
  switch (wave) {
    case 1:
      memcpy(waveform, risingSaw, sizeof waveform);
      break;
    case 2:
      memcpy(waveform, fallingSaw, sizeof waveform);
      break;
    case 3:
      memcpy(waveform, squareWave, sizeof waveform);
      break;
//    default:
//      memcpy(waveform, sineWave, sizeof waveform);
//      break;
  }

  // Check the proper waveform was loaded
  for (int ii=0; ii<res; ++ii) Serial.print(waveform[ii]);
}



void setup() {
  // Open serial monitor at 9600 baud
  Serial.begin(9600);

  // Set pinmodes for output
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);

  // Select waveform
  pickWaveform();
}



void loop() {
  for (int ii = 0; ii < res; ++ii){  
    // Check digit value
    Serial.print(waveform[ii]);
    Serial.print("  ");
    Serial.println(waveform[ii], BIN);

    // Set pin outputs by binary number
    digitalWrite(a0, HIGH && (waveform[ii] & B00000001));
    digitalWrite(a1, HIGH && (waveform[ii] & B00000010));
    digitalWrite(a2, HIGH && (waveform[ii] & B00000100));

    delay(1000);
    }
}
