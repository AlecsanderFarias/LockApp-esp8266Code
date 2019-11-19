#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


#define led D0

int status;

const char* ssid = "LockAppHouse";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(led, OUTPUT);
 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  digitalWrite(led,LOW);
  status = 0;
 
 // Starting WEB-server 
     server.on ( "/",  test);
     server.on ( "/on", turnOn );
     server.on ( "/off", turnOff );
     server.on ( "/status",  getStatus);
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}



void loop() {
    server.handleClient();
}


void test(){
  String message = "{ status= conectado }";
  server.send(200, "application/json", message);
}

void turnOn(){
  status = 1;
  digitalWrite(led,HIGH);
}

void turnOff(){
  status = 0;
  digitalWrite(led,LOW);
}


void getStatus(){
  String message = "{ ";
  message += " status= ";
  message += status == 1 ? "on " : "off ";
  message += " }";
  server.send(200, "application/json", message);
}

void HTTP_handleRoot(){
  server.send(200, "text/plain", "url nao existente");
}
