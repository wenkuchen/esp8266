#include <Arduino.h>
#include "config.h"
#include "init.h"

void wifi_init(WiFiMode mode){ //WIFI_AP_STA or WIFI_AP
    WiFi.mode(mode);
    if(mode == WIFI_AP_STA){
        WiFi.begin(DEF_SSID,DEF_PASSWORD);
        while(WiFi.waitForConnectResult()!=WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }
        Serial.println(); Serial.print("Connected, IP: ");
        Serial.println(WiFi.localIP());
    } else if(mode == WIFI_AP) {
        while(!WiFi.softAP(DEF_SSID,DEF_PASSWORD)) delay(200);
        Serial.println("AP successful bootup.");
        Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
    }
}

void fs_init(){
    if(!LittleFS.begin())
        Serial.println("Cannot mount LittleFS volume...");
}

String processor() { return String("l");}

void handleRoot(AsyncWebServerRequest *req){
    req->send(LittleFS,"/index.html",false,processor);
}
AsyncWebServer server(80);
void webserver_init(){
    server.on("/",handleRoot);
    server.begin();
}

void esp_init(){
    fs_init();
    wifi_init(WIFI_AP_STA); // or WIFI_AP
    webserver_init();

}
