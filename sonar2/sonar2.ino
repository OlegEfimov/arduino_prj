#include <stdio.h>
#include "pins_arduino.h"


#include <Arduino.h>

//#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
//#include <WebSocketsServer.h>
//#include <Hash.h>



// #define USE_SERIAL Serial1
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
static int  tmp777 = 0;
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

unsigned long time1;
unsigned long time2;

unsigned long d1;
unsigned long d2;
unsigned long d3;
unsigned long d4;
unsigned long d5;
unsigned long d6;
char tbs[500];
char divider;
String tmpString = "100,\t200,\t300,\t400,\t500,\t600;";

const int LENGHT_BUF_IN = 400;
//const int LENGHT_BUF_OUT = 100;

//char buf_out[LENGHT_BUF_OUT];
char buf_in[LENGHT_BUF_IN];
int lenght_in;
int lenght_out;


//String inputString = "";         // a String to hold incoming data
//bool stringComplete = false;  // whether the string is complete


void setup() {

//  // reserve 200 bytes for the inputString:
//  inputString.reserve(200);

  divider = ';';
// motor
// pinMode (ENA, OUTPUT); 
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
//  pinMode (ENB, OUTPUT); 

  Serial.begin (115200);
  Serial2.begin (115200);

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

  Serial2.setTimeout(60);
  Serial.println("setup mega ");
//  Serial.flush();
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
 
void getDistanceData()
{
    d1 = getDistance(trigPin0 , echoPin0);
    d2 = getDistance(trigPin1, echoPin1);
    d3 = getDistance(trigPin2, echoPin2);
    d4 = getDistance(trigPin3, echoPin3);
    d5 = getDistance(trigPin4, echoPin4);
    d6 = getDistance(trigPin5, echoPin5);

    Serial2.print(d1);
    Serial2.print(",\t");

    Serial2.print(d2);
    Serial2.print(",\t");

    Serial2.print(d3);
    Serial2.print(",\t");

    Serial2.print(d4);
    Serial2.print(",\t");

    Serial2.print(d5);
    Serial2.print(",\t");

    Serial2.print(d6);
    Serial2.print(";");
    
//    Serial2.print("=00=");
}

void loop()
{
//  // print the string when a newline arrives:
//  if (stringComplete) {
////Serial.println("---loop if (stringComplete))---");
////    Serial.println(inputString);
//      if (inputString.length() > 3) {
////        buf_in[lenght_in] = 0;
////        String commandStr(buf_in);
//        int pos1 = inputString.indexOf('=');
//        int pos2 = inputString.indexOf('=', pos1+1);
//        String command1 = inputString.substring(0, pos1);
//        String command2 = inputString.substring(pos1+1, pos2);
//
////         Serial.write(buf_in, lenght_in);
//        Serial.println("--------start---------");
//        Serial.println(inputString);
//        Serial.println(inputString.length());
//        Serial.println(pos1);
//        Serial.println(pos2);
//        Serial.println(command1);
//        Serial.println(command2);
//        Serial.println("--------end-----------");
//      } else {
////        Serial2.write(buf_in, lenght_in);
//        Serial.println("--------=<3-----------");
////        Serial.println();
//      }
//
//    // clear the string:
//    inputString = "";
//    stringComplete = false;
//  }

// {
//     if (Serial2.available() > 0){
//       String commands = Serial2.readUntil(divider);
//       if (commands.lenght() > 3) {
//         Serial.write(commands);
//       } else {
//         Serial.println();
//       }
//     }
//     getDistanceData();
//     delay(60);
// }


//{
    if (Serial2.available() > 0){
      for (int i = 0; i < 50; i++) {
        buf_in[i]=0;
      }
//      Serial2.print(" =0= ");
      lenght_in = Serial2.readBytesUntil(divider, buf_in, LENGHT_BUF_IN);
      if (lenght_in > 3 && lenght_in < 11) {
        buf_in[lenght_in] = 0;
        String commandStr(buf_in);
        int pos1 = commandStr.indexOf('=');
        int pos2 = commandStr.indexOf('=', pos1+1);
        String command1 = commandStr.substring(0, pos1);
        String command2 = commandStr.substring(pos1+1, pos2);

//         Serial.write(buf_in, lenght_in);
//        Serial.println("--------start---------");
//        Serial.println(commandStr);
//        Serial.println(lenght_in);
//        Serial.println(pos1);
//        Serial.println(pos2);
        Serial.println(command1);
        Serial.println(command2);
//        Serial.println("--------end-----------");
      } else {
//        Serial2.write(buf_in, lenght_in);
        Serial.println("--------=<3-----------");
//        Serial.println();
      }
    }
    getDistanceData();
    delay(60);
}

//void serialEvent2() {
////Serial.println("---serialEvent()---");
//
//    // get the new byte:
//    char inChar = (char)Serial2.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag so the main loop can
//    // do something about it:
//    if (inChar == divider) {
//      stringComplete = true;
//     }
//  }
//  
