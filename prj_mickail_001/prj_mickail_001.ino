#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2); // Указываем I2C адрес = 0x3f
                                  // параметры экрана - 2 строки по 16 символов в каждой
const int trigPin = 9;
const int echoPin = 8;
const int CYCLE_NUMBER = 10;
long duration;
long sumDuration;
int counter;

void setup() {
  counter = 0;
  sumDuration = 0;
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("---Instant value");
  lcd.setCursor(0,1);
  lcd.print("---Average value");
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

  lcd.setCursor(0,0);
  lcd.print("inst: ");
  lcd.print(duration);
  lcd.print(" mks      ");

  counter += 1;
  sumDuration += duration;
  if (counter >= CYCLE_NUMBER) {
    lcd.setCursor(0,1);
    lcd.print("mean: ");
    lcd.print(sumDuration / CYCLE_NUMBER);
    lcd.print(" mks        ");
    sumDuration = 0;
    counter = 0;
  }
  delay(200);
}