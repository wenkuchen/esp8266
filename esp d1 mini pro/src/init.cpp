#include <Arduino.h>
#include "config.h"
#include "init.h"

void wifi_init(WiFiMode mode){ //WIFI_AP_STA or WIFI_AP
    WiFi.disconnect();
    WiFi.mode(mode);
    if(mode == WIFI_AP_STA){
        WiFi.begin(DEF_SSID,DEF_PASSWORD);
        while(WiFi.waitForConnectResult()!=WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }
        Serial.println(); Serial.print("Connected, IP: ");
        Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
    } else if(mode == WIFI_AP) {
        while(!WiFi.softAP(DEF_SSID,DEF_PASSWORD)) delay(200);
        Serial.println("AP successful bootup.");
        Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
    }
}

/** For ESP32 use #include <SPIFFS.h> and SPIFFS.begin()
void fs_init(){
    if(!SPIFFS.begin())
        Serial.println("Cannot mount LittleFS volume...");
} **/
void fs_init(){
    if(!LittleFS.begin())
        Serial.println("Cannot mount LittleFS volume...");
}

AsyncWebServer server(80);

void webserver_init(){
    server.on("/",[](AsyncWebServerRequest *req){
        req->send(LittleFS,"/index.html","text/html");
    });

    server.serveStatic("/", LittleFS, "/"); // files css js files located same as root

    server.onNotFound([](AsyncWebServerRequest *request){
	    request->send(404, "text/plain", "not Found!"); });

    server.begin();
}

void esp8266_init(){
    fs_init();
    wifi_init(WIFI_AP_STA); // or WIFI_AP
    webserver_init();
}
