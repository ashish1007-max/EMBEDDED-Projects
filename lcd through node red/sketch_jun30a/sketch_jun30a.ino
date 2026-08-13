#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);

  // ESP32 I2C pins
  Wire.begin(21,22);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }

  // Set RTC only if it is stopped
  Serial.println("Setting RTC to compile time...");
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {

  DateTime now = rtc.now();

  // Serial Monitor
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.print(now.year());

  Serial.print("   ");

  Serial.print(now.hour());
  Serial.print(":");

  if(now.minute()<10) Serial.print("0");
  Serial.print(now.minute());

  Serial.print(":");

  if(now.second()<10) Serial.print("0");
  Serial.println(now.second());

  // OLED
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("TIME");

  display.setCursor(0,20);

  if(now.hour()<10) display.print("0");
  display.print(now.hour());
  display.print(":");

  if(now.minute()<10) display.print("0");
  display.print(now.minute());
  display.print(":");

  if(now.second()<10) display.print("0");
  display.print(now.second());

  display.setTextSize(1);
  display.setCursor(0,50);

  if(now.day()<10) display.print("0");
  display.print(now.day());
  display.print("/");

  if(now.month()<10) display.print("0");
  display.print(now.month());
  display.print("/");

  display.print(now.year());

  display.display();

  delay(1000);
}