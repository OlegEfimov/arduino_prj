#include <stdio.h>
#include "pins_arduino.h"
#include <Arduino.h>


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WebSocketsServer.h>
#include <Hash.h>

const char* ssid = "Berg";
const char* password = "robinbobin315";

WebSocketsServer webSocket = WebSocketsServer(81);

char divider;

/////////////////////////////
const int LENGHT_BUF_IN = 400;

char buf_in[LENGHT_BUF_IN];
int lenght_in;

int intCmd1;
int intCmd2;

// const int IN1 = 26;
// const int IN2 = 27;
// const int IN3 = 25;
// const int IN4 = 33;

const int ledPin1 = 26;
const int ledPin2 = 27;
const int ledPin3 = 25;
const int ledPin4 = 33;
const int freq = 5000;
const int ledChannel_1 = 0;
const int ledChannel_2 = 1;
const int ledChannel_3 = 2;
const int ledChannel_4 = 3;
const int resolution = 8;

int cmdReady = 0;

/////////////////////////////

void setup() {
  delay(5000);
  divider = ';';
  Serial.begin(115200);
  Serial.setTimeout(60);
  Serial.println("");
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  delay(5000);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

////////control engine//////////////
  // pinMode (IN1, OUTPUT);
  // pinMode (IN2, OUTPUT);
  // pinMode (IN3, OUTPUT);
  // pinMode (IN4, OUTPUT);

  ledcSetup(ledChannel_1, freq, resolution);
  ledcSetup(ledChannel_2, freq, resolution);
  ledcSetup(ledChannel_3, freq, resolution);
  ledcSetup(ledChannel_4, freq, resolution);

  ledcAttachPin(ledPin1, ledChannel_1);
  ledcAttachPin(ledPin2, ledChannel_2);
  ledcAttachPin(ledPin3, ledChannel_3);
  ledcAttachPin(ledPin4, ledChannel_4);

////////////////////////////////////
}

void loop() {
  webSocket.loop();
////////control engine//////////////
  if (cmdReady > 0) {
    String commandStr(buf_in);
    int pos1 = commandStr.indexOf('=');
    int pos2 = commandStr.indexOf('=', pos1+1);
    String command1 = commandStr.substring(0, pos1);
    String command2 = commandStr.substring(pos1+1, pos2);
    intCmd1 = command1.toInt();
    intCmd2 = command2.toInt();
    Serial.println(intCmd1);
    Serial.println(intCmd2);
    Serial.println(commandStr);

    if (intCmd1 > 0) {
      // analogWrite(IN1,0);
      // analogWrite(IN2,intCmd1);
      ledcWrite(ledChannel_1, 0);
      ledcWrite(ledChannel_2, intCmd1);
    } else {
      // analogWrite(IN1,-intCmd1);
      // analogWrite(IN2,0);
      ledcWrite(ledChannel_1, -intCmd1);
      ledcWrite(ledChannel_2, 0);
    }
    if (intCmd2 > 0) {
      // analogWrite(IN3,0);
      // analogWrite(IN4,intCmd2);
      ledcWrite(ledChannel_3, 0);
      ledcWrite(ledChannel_4, intCmd2);
    } else {
      // analogWrite(IN3,-intCmd2);
      // analogWrite(IN4,0);
      ledcWrite(ledChannel_3, -intCmd2);
      ledcWrite(ledChannel_4, 0);
    }
    cmdReady = 0;
  }

  delay(10);
////////////////////////////////////
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if (type == WStype_TEXT){
    for (int i = 0; i < LENGHT_BUF_IN; i++) {
      buf_in[i]=0;
    }
    for(int i = 0; i < length; i++) {
      buf_in[i] = payload[i];
    }
    cmdReady = 1;
  }
}

