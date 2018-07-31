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

int trigPin0 = 22;
int echoPin0 = 23;
int trigPin1 = 24;
int echoPin1 = 25;
int trigPin2 = 26;
int echoPin2 = 27;

int trigPin3 = 28;
int echoPin3 = 29;
int trigPin4 = 30;
int echoPin4 = 31;
int trigPin5 = 32;
int echoPin5 = 33;

unsigned long d1;
unsigned long d2;
unsigned long d3;
unsigned long d4;
unsigned long d5;
unsigned long d6;
char tbs[500];
char divider;

const int LENGHT_BUF_IN = 200;
const int LENGHT_BUF_OUT = 100;

char buf_out[LENGHT_BUF_OUT];
char buf_in[LENGHT_BUF_IN];
int lenght_in;
int lenght_out;

void setup() {

  divider = ';';
// motor
// pinMode (ENA, OUTPUT); 
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
//  pinMode (ENB, OUTPUT); 

  Serial.begin (115200);
  Serial3.begin (115200);

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

  Serial3.setTimeout(100);
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
  if (Serial3.available() > 0){
    lenght_in = Serial3.readBytesUntil(divider, buf_in, LENGHT_BUF_IN);
    Serial.write(buf_in, lenght_in);
  }
  
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
}
