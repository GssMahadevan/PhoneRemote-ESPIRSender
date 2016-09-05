/*
 * IRremoteESP8266: IRServer - demonstrates sending IR codes controlled from a webserver
 * An IR LED must be connected to ESP8266 pin 0.
 * Version 0.1 June, 2015
 * Version 0.2 June, 2015
   
   Made modification to IRremoteESP8266's IRServer program to link to python server (whcih serves
   all smart-phone's remote app) .

   TODO: 
      * Security & authentication
      * Length check of codes & error-checking atoi
      * Rate control of http requests

  Author: GSS Mahadevan
  Version: 0.3  5-Sep-2016
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <string.h>
 
const char* ssid = "Your_wifi_SSID_name";
const char* password = "Your_wifi_SSID_password" ;
MDNSResponder mdns;

ESP8266WebServer server(80);

IRsend irsend(D6);
https://bbs.nextthing.co/users/nealpalmer
extern void sendRawCode(IRsend &irsend, int   what);

#define HELP "<html><head> <title>ESP8266 Demo</title></head><body><h1>" \
"Hello from ESP8266, you can send NEC encoded IR signals from here!</h1><br><p><a href=\"ir?code=2800,900,500,450,500,450,500,900,550,900,1450,900,"\
"500,450,500,450,500,450,500,450,500,450,500,450,500,450,500,450,1000,900,500,450,500,450,1000,450,500,900,500,450,500,450,500,450,500,450,500,"\
"450,500,450,500,450,500,450,500,450,500,450,500,450,1000,450,500,900,1000&hz=38&count=1\">Send IR code</a>" \
"</p></body></html>"


void handleRoot() {
 server.send(200, "text/html", HELP);
}

const int MAX_CODES=128;

void handleIr(){
  unsigned int codes[MAX_CODES];
  int hz=38;
  int len=0;
  int aLen=0;
  bool err=false;
  int count=1;
  for (uint8_t i=0; i<server.args(); i++){
    if(server.argName(i) == "code")    {
      String code = server.arg(i);      
      char *p = (char*) code.c_str(); ;
      char *str;
      int i=0;
      
      while ((str = strtok_r(p, ",", &p)) != NULL) {
          //Serial.println(str);
          if(i >= MAX_CODES) {
              Serial.printf("Crossed max ir-code size:%d\n",i);
              err=true;
              break;
          }
          
          codes[i++]=atoi(str);
      }
      aLen=i;
    }else if(server.argName(i) == "hz")  {
      hz  = server.arg(i).toInt();
      if(hz < 30 || hz > 100) hz=38;
    }else if(server.argName(i) == "count")  {
      count  = server.arg(i).toInt();
      if(count < 0 || count > 3) count=0;
    }
  }
  if(!err){
    // Need to debug for sending multiple IR calls from here. Currently disabled  & python server will do it from server
    //for(int i=0;i<count;i++) 
      irsend.sendRaw(codes,aLen,hz);
      //delay(5);
  }
  server.send (err ? 400 : 200, "text/json", "{}");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void){
  irsend.begin();
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  server.on("/ir", handleIr); 
 
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
