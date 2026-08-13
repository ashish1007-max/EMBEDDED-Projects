const int dataPin = 11;
const int clockPin = 12;
const int latchPin = 8;

void setup()
{
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop()
{
  for (byte i = 0; i < 8; i++)
  {
    digitalWrite(latchPin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, 1 << i);

    digitalWrite(latchPin, HIGH);

    delay(200);
  }
}