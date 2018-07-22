/*
 * Автор – Руи Сантос (Rui Santos); http://randomnerdtutorials.com
 *
 * Скетч сделан для руководства по ультразвуковому датчику HC-SR04
 *
 * Подключение контактов:
 * VCC: к +5 вольтам постоянного тока
 * Trig (входной): к контакту 11
 * Echo (выходной): к контакту 12
 * GND: к контакту GND
 */
#include <stdio.h>
#include "pins_arduino.h"
//////////////////////
// motor setup
// http://zelectro.cc/Motor_shield_L298N_Arduino
////////////////////// 
//int ENA = 9;
//int IN1 = 7;
//int IN2 = 6;
//int IN3 = 5;
//int IN4 = 4;
//int ENB = 3;
int IN1 = 10;
int IN2 = 11;
int IN3 = 46;
int IN4 = 44;

int i;
///////////////////////

int trigPin0 = 22;    // Trig – зеленый провод-перемычка
int echoPin0 = 23;    // Echo – желтый провод-перемычка
int trigPin1 = 24;    // Trig – зеленый провод-перемычка
int echoPin1 = 25;    // Echo – желтый провод-перемычка
int trigPin2 = 26;    // Trig – зеленый провод-перемычка
int echoPin2 = 27;    // Echo – желтый провод-перемычка

int trigPin3 = 28;
int echoPin3 = 29;
int trigPin4 = 30;
int echoPin4 = 31;
int trigPin5 = 32;
int echoPin5 = 33;

//int trigPin3 = 6;
//int echoPin3 = 7;
//int trigPin4 = 8;
//int echoPin4 = 9;
//int trigPin5 = 10;
//int echoPin5 = 11;

//int trigPin6 = 12;
//int echoPin6 = 13;
//unsigned long cm;
//unsigned long cm2;
//unsigned long duration;
//unsigned long duration2;
unsigned long d1;
unsigned long d2;
unsigned long d3;
unsigned long d4;
unsigned long d5;
unsigned long d6;
char tbs[500];
//unsigned long prevTime;
//unsigned long currentTime;

const int LENGHT_BUF_IN = 200;
const int LENGHT_BUF_OUT = 100;

char buf_out[LENGHT_BUF_OUT];
char buf_in[LENGHT_BUF_IN];
int lenght_in;
int lenght_out;

//int dbgvalue1;
//int dbgvalue2;
//int dbgvalue3;
//int dbgvalue4;
//int dbgvalue5;

void setup() {
// motor
// pinMode (ENA, OUTPUT); 
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
// pinMode (ENB, OUTPUT); 


//  dbgvalue1 = 0;
//  dbgvalue2 = 0;
//  dbgvalue3 = 0;
//  dbgvalue4 = 0;
//  dbgvalue5 = 0;
//  prevTime = millis();
  // открываем последовательный порт:
  Serial.begin (115200);
  Serial3.begin (115200);
  // задаем входные и выходные контакты:
//  pinMode(trigPin1, OUTPUT);
//  pinMode(echoPin1, INPUT);
//  pinMode(trigPin2, OUTPUT);
//  pinMode(echoPin2, INPUT);

//  pinMode(PIN_A0, OUTPUT);
//  digitalWrite(PIN_A0, HIGH);
//  pinMode(PIN_A1, INPUT);
//  digitalWrite(PIN_A1, HIGH);
//
//  pinMode(PIN_A2, OUTPUT);
//  digitalWrite(PIN_A2, HIGH);
//  pinMode(PIN_A3, INPUT);
//  digitalWrite(PIN_A3, HIGH);
//
//  pinMode(PIN_A4, OUTPUT);
//  digitalWrite(PIN_A4, HIGH);
//  pinMode(PIN_A5, INPUT);
//  digitalWrite(PIN_A5, HIGH);
//
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);
//  pinMode(trigPin6, OUTPUT);
//  pinMode(echoPin6, INPUT);
  
//  currentTime = millis();
//  Serial3.print("setup-");
//  Serial3.println(currentTime - prevTime);
}

unsigned long getDistance(int trigPin, int echoPin)
{
  unsigned long _distance;
  unsigned long _duration;
  // датчик запускается импульсом HIGH продолжительностью 10 мкс
  // или более; но перед этим нужно подать короткий импульс LOW,
  // чтобы Trig в конце концов получил четкий импульс HIGH:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // считываем сигнал от датчика; продолжительность импульса HIGH –
  // это время, прошедшее от отправки импульса
  // до получения эха от объекта:
  pinMode(echoPin, INPUT);
  _duration = pulseIn(echoPin, HIGH, 30000);
  _distance = (_duration/2) / 2.91;
  return _distance;
}
 
void loop()
{
//  prevTime  = currentTime;
//  currentTime = millis();
//  Serial.println(currentTime - prevTime);
//  while (Serial3.available()) {
//    int inByte = Serial3.read();
//    Serial.write(inByte);
//  }
//  if (Serial.available()) {
//    int inByte = Serial.read();
//    Serial3.write(inByte);
//  }

    if (Serial3.available() > 0){
      lenght_in = Serial3.readBytes(buf_in, LENGHT_BUF_IN);
      Serial.write(buf_in, lenght_in);
    }
//    if (Serial.available() > 0){
//      lenght_out = Serial.readBytes(buf_out, LENGHT_BUF_OUT);
//      Serial3.write(buf_out, lenght_out);
//    }

//  for (int i = trigPin2; i < 14; i=i+2) {
//    Serial3.print(getDistance(i, i+1));
//    Serial3.print(",");
////    delay(10);s
//  }
//  Serial3.print(getDistance(trigPin2, echoPin2));
//  Serial3.print(",");
//
//  Serial.print(getDistance(PIN_A0, PIN_A1));
//  Serial.print(",");
//
//  Serial.print(getDistance(trigPin3, echoPin3));
//  Serial.print(",");
//  
//  Serial.print(getDistance(trigPin4, echoPin4));
//  Serial.print(",");
//  
//  Serial.print(getDistance(trigPin5, echoPin5));
//  Serial.print(",");
//  
//  Serial.print(getDistance(trigPin6, echoPin6));

  d1 = getDistance(trigPin0 , echoPin0);
//  delay(10);
  d2 = getDistance(trigPin1, echoPin1);
//  delay(10);
  d3 = getDistance(trigPin2, echoPin2);
//  delay(10);
  d4 = getDistance(trigPin3, echoPin3);
//  delay(10);
  d5 = getDistance(trigPin4, echoPin4);
//  delay(10);
  d6 = getDistance(trigPin5, echoPin5);
//  delay(10);
//  d6 = getDistance(trigPin6, echoPin6);

//  dbgvalue1 = (dbgvalue1 + 1)%700;
//  d1 = dbgvalue1;
//  dbgvalue2 = (dbgvalue2 + 5)%700;
//  d2 = dbgvalue2;
//  dbgvalue3 = (dbgvalue3 + 10)%700;
//  d3 = dbgvalue3;
//  dbgvalue4 = (dbgvalue4 + 15)%700;
//  d4 = dbgvalue4;
//  dbgvalue5 = (dbgvalue5 + 20)%700;
//  d5 = dbgvalue5;

//  d1 = 100;
//  d2 = 200;
//  d3 = 300;
//  d4 = 400;
//  d5 = 500;

//  sprintf(tbs, "%d,%d,%d,%d,%d;",d1,d2,d3,d4,d5);
//  Serial.println(tbs);
//  Serial.println(tbs);

//  Serial3.print(d1);
//  Serial3.print(",");
//
//  Serial3.print(d2);
//  Serial3.print(",");
//  
//  Serial3.print(d3);
//  Serial3.print(",");
//  
//  Serial3.print(d4);
//  Serial3.print(",");
//  
//  Serial3.print(d5);
//  Serial3.print(",");
//  
//  Serial3.print(d6);
//  Serial3.println(";");
//
  Serial3.print(d1);
  Serial3.print(",\t");

  Serial3.print(d2);
  Serial3.print(",\t");
  
  Serial3.print(d3);
  Serial3.print(",\t");
  
  Serial3.print(d4);
  Serial3.print(",\t");
  
  Serial3.print(d5);
  Serial3.print(",\t");
  
  Serial3.print(d6);
  Serial3.println(";");
  
  delay(200);
//    Serial3.write(0);
//  delay(250);

/////////////////////////////
// analogWrite(IN1,0);
// analogWrite(IN2,0);
// analogWrite(IN3,0);
// analogWrite(IN4,0);
// delay(2000);
// analogWrite(IN2,100);
// analogWrite(IN4,100);
// delay(2000);
// analogWrite(IN1,0);
// analogWrite(IN2,0);
// analogWrite(IN3,0);
// analogWrite(IN4,0);
// delay(2000);
//analogWrite(IN2,155);
// analogWrite(IN4,155);
// delay(2000);
// analogWrite(IN1,0);
// analogWrite(IN2,0);
// analogWrite(IN3,0);
// analogWrite(IN4,0);
// delay(2000);
// analogWrite(IN1,255);
// analogWrite(IN3,255);
// delay(2000);
// analogWrite(IN1,0);
// analogWrite(IN2,0);
// analogWrite(IN3,0);
// analogWrite(IN4,0);
// delay(2000);
// analogWrite(IN1,55);
// analogWrite(IN3,55);
// delay(2000);
///////////////////////
}
