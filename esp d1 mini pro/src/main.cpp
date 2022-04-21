#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#include "config.h"

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP_STA); 
  WiFi.begin("WCK","23752755");
  
  Serial.begin(115200);
	delay(20);
  
  //test();
}

void loop() {
  
  // put your main code here, to run repeatedly:
}