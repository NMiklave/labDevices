int a0=2;
int a1=3;
int a2=4;

void setup() {
  // put your setup code here, to run once:
  // Open serial monitor at 9600 baud
  Serial.begin(9600);

  // Set pinmodes for output
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Loop from 0 to 3
  for (int digit=0; digit<8; ++digit){
    // Check digit value
    Serial.print(digit);
    Serial.print("  ");
    Serial.println(digit, BIN);

    // Set pin outputs by binary number
    digitalWrite(a0, HIGH && (digit & B00000001));
    digitalWrite(a1, HIGH && (digit & B00000010));
    digitalWrite(a2, HIGH && (digit & B00000100));

    // Wait 500 ms (0.5 Hz for a 2 bit DAC)
    delay(500);
    }
}
