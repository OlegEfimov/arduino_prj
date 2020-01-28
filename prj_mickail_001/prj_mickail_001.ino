#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой
const int trigPin = 9;
const int echoPin = 8;
long duration;
long sumDuration;
int distanceCm, distanceInch, counter;

void setup() {
  counter = 0;
  sumDuration = 0;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(0,1);
  lcd.print("ArduinoMaster");
  delay(3000);
  lcd.clear();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
//  distanceCm= duration*0.0343/2;
//  distanceInch = duration*0.0133/2;

  lcd.setCursor(0,0);
  lcd.print("t: ");
  lcd.print(duration);
  lcd.print(" mks      ");
  delay(10);
  counter += 1;
  sumDuration += duration;
  if (counter >= 10) {
    lcd.setCursor(0,1);
    lcd.print("t: ");
    lcd.print(sumDuration / 10);
    lcd.print(" mks        ");
    sumDuration = 0;
    counter = 0;
  }
  delay(200);
}
