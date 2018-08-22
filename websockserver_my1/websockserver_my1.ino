#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>

const char* ssid = "ZyXEL_KEENETIC_LITE_7939DF";
const char* password = "StateMachine-12";

// String WebPage = "<!DOCTYPE html><html><style>input[type=\"text\"]{width: 90%; height: 3vh;}input[type=\"button\"]{width: 9%; height: 3.6vh;}.rxd{height: 90vh;}textarea{width: 99%; height: 100%; resize: none;}</style><script>var Socket;function start(){Socket=new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage=function(evt){document.getElementById(\"rxConsole\").value +=evt.data;}}function enterpressed(){Socket.send(document.getElementById(\"txbuff\").value); document.getElementById(\"txbuff\").value=\"\";}</script><body onload=\"javascript:start();\"> <div><input class=\"txd\" type=\"text\" id=\"txbuff\" onkeydown=\"if(event.keyCode==13) enterpressed();\"><input class=\"txd\" type=\"button\" onclick=\"enterpressed();\" value=\"Send\" > </div><br><div class=\"rxd\"> <textarea id=\"rxConsole\" readonly></textarea> </div></body></html>";

WebSocketsServer webSocket = WebSocketsServer(81);
//ESP8266WebServer server(80);

// unsigned long prevTime;
// unsigned long currentTime;

const int LENGHT_BUF_IN = 200;
//const int LENGHT_BUF_OUT = 100;

//char buf_out[LENGHT_BUF_OUT];
char buf_in[LENGHT_BUF_IN];
char divider;

void setup() {
  delay(5000);
  // prevTime = millis();
  divider = ';';
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
    
//    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println(divider);

    Serial.flush();

//    server.on("/", [](){
//    server.send(200, "text/html", WebPage);
//    });
    
//    server.begin();
    delay(5000);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

  // currentTime = millis();
  // Serial.print("setup8266-");
  // Serial.println(currentTime - prevTime);
}

void loop() {
  // prevTime  = currentTime;
  // currentTime = millis();
//  Serial.println(currentTime - prevTime);

    webSocket.loop();
//    server.handleClient();
//    if (Serial.available() > 0){
//      char c[] = {(char)Serial.read()};
//      webSocket.broadcastTXT(c, sizeof(c));
//    }
    if (Serial.available() > 0){
      int lenght_in = Serial.readBytesUntil(divider, buf_in, LENGHT_BUF_IN);
      webSocket.broadcastTXT(buf_in, lenght_in);
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
    Serial.print("=");
   if (type == WStype_TEXT){
    for(int i = 0; i < length; i++) Serial.print((char) payload[i]);
    Serial.println();
    Serial.flush();
   }
}
