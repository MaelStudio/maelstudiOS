#include "I2C_BM8563.h"

I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(50);

  Wire.begin();
  rtc.begin();

  Serial.println("Send date as DD/MM/YYYY HH:MM:SS W to program the RTC");
  Serial.println("Example: 27/05/2025 19:34:02 2");
  Serial.println("W is day of week. 0=monday 6=sunday");
}

void loop() {
  I2C_BM8563_DateTypeDef dateStruct;
  I2C_BM8563_TimeTypeDef timeStruct;

  // Check for user input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Format: DD/MM/YYYY HH:MM:SS W
    int day, month, year, hour, minute, second, weekday;
    if (sscanf(input.c_str(), "%d/%d/%d %d:%d:%d %d", &day, &month, &year, &hour, &minute, &second, &weekday) == 7) {

      // PROGRAM THE RTC
      dateStruct.year = year;
      dateStruct.month = month;
      dateStruct.date = day;
      dateStruct.weekDay = weekday;

      timeStruct.hours = hour;
      timeStruct.minutes = minute;
      timeStruct.seconds = second;

      rtc.setDate(&dateStruct);
      rtc.setTime(&timeStruct);

      Serial.println("RTC updated!");
    } else {
      Serial.println("Invalid format. Use: DD/MM/YYYY HH:MM:SS W");
    }
  }

  // READ DATE & TIME FROM RTC
  rtc.getDate(&dateStruct);
  rtc.getTime(&timeStruct);

  Serial.printf("%02d/%02d/%04d %02d:%02d:%02d Weekday: %d\n",
                dateStruct.date,
                dateStruct.month,
                dateStruct.year,
                timeStruct.hours,
                timeStruct.minutes,
                timeStruct.seconds,
                dateStruct.weekDay);

  delay(1000);
}