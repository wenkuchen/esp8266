#include <Arduino.h>
#include "config.h"
#include "init.h"

void wifi_init(){
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(SSID,PASSWORD);
    while(WiFi.waitForConnectResult()!=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println(); Serial.print("Connected, IP: ");
    Serial.println(WiFi.localIP());
}

void handleRoot(){}
void webserver_init(){
    static AsyncWebServer server(80);
    //server.on("/",handleRoot);
    server.begin();
}

void esp_init(){
    wifi_init();
    webserver_init();
}
