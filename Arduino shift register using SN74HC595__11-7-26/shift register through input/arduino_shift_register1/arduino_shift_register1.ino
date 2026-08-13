const int dataPin  = 11;   // DS
const int clockPin = 12;   // SHCP
const int latchPin = 8;    // STCP

String inputBits = "";

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  Serial.begin(9600);

  Serial.println("Enter 8 bits (example: 10110010)");
}

void loop() {
  if (Serial.available()) {

    inputBits = Serial.readStringUntil('\n');
    inputBits.trim();

    // Check length
    if (inputBits.length() != 8) {
      Serial.println("Error: Enter exactly 8 bits.");
      return;
    }

    // Convert string to byte
    byte value = 0;

    for (int i = 0; i < 8; i++) {
      char bitChar = inputBits.charAt(i);

      if (bitChar == '1') {
        value |= (1 << (7 - i));   // Set corresponding bit
      }
      else if (bitChar != '0') {
        Serial.println("Error: Use only 0 and 1.");
        return;
      }
    }

    // Send to shift register
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, value);
    digitalWrite(latchPin, HIGH);

    // Show stored value
    Serial.print("Stored in register: ");
    Serial.println(inputBits);
  }
}