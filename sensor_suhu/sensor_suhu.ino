/*
Program Mengukur Suhu dan Kelembaban
Arduino Uno
Loki Lang
*/

#include <LiquidCrystal.h>
#include <SHT1x.h>
#define dataPin 9
#define clockPin 10

LiquidCrystal lang(4, 5, 6, 7, 8, 9);
SHT1x feli(dataPin, clockPin);

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino SHT11");
  lang.begin(16, 2);
  lang.setCursor(0, 0);
  lang.print("Arduino SHT11");
  delay(1000);
}

void loop()
{
  float temp_c;
  float humidity;

  temp_c = feli.readTemperatureC();
  humidity = feli.readHumidity();

  Serial.print("Suhu: ");
  Serial.print(temp_c, DEC);
  Serial.println(" celsius");
  lang.clear();
  lang.setCursor(0, 0);
  lang.print("Suhu: ");
  lang.setCursor(6, 0);
  lang.print(temp_c, DEC);
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");
  lang.setCursor(0, 1);
  lang.print("Kelembaban: ");
  lang.setCursor(12, 1);
  lang.print(humidity);
  delay(500);
}

