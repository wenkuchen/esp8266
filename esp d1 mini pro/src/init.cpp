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

String processor(const String &var) { return String("l");}

void handleRoot(AsyncWebServerRequest *req){
    //req->send(LittleFS,"/index.html",false,processor);
    //compiling problems req->send()
}

AsyncWebServer server(80);

void webserver_init(){
    //server.on("/",handleRoot);  // use fs index.html
    //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){request->send(200, "text/plain", "Hello World!");});
    server.on("/",[](AsyncWebServerRequest *req){
        //req->send(LittleFS,"/index.html",String(),false, processor);
        req->send(LittleFS,"/index.html","text/html");
    });
    //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){request->send(LittleFS, "/index.html", String(), false, processor);});
//server.serveStatic("/", SPIFFS, "/", CACHE_HEADER).setDefaultFile("index.html");

    server.onNotFound([](AsyncWebServerRequest *request){
	    request->send(404, "text/plain", "not Found!"); });

    server.begin();
}

void esp_init(){
    fs_init();
    wifi_init(WIFI_AP_STA); // or WIFI_AP
    webserver_init();

}
