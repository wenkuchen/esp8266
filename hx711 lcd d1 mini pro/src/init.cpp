#include <Arduino.h>
#include <ArduinoJson.h>
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
        else Serial.println("SPIFFS mounted!");
} **/
void fs_init(){
    if(!LittleFS.begin())
        Serial.println("Cannot mount LittleFS volume...");
        else Serial.println("LittleFS mounted!");
}

AsyncWebServer server(80); //default http webserver port at 80

// Create a WebSocket object
AsyncWebSocket ws("/ws");

void webserver_init(){
    server.on("/",[](AsyncWebServerRequest *req){
        req->send(LittleFS,"/index.html","text/html");
    });

    server.serveStatic("/", LittleFS, "/"); // files css js files located same as root

    server.onNotFound([](AsyncWebServerRequest *request){
	    request->send(404, "text/plain", "not Found!"); });

    server.begin();
}

void notifyClients(String state) {
ws.textAll(state);
}

void handleClientWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    // deserializeJson from *data which is JSON formatted
    StaticJsonDocument<200> doc;
    deserializeJson(doc,(char*)data);
    ws.textAll("dkdk"); // String to all clients
}

void handleClientWebSocketMessage(uint8_t* jdata){

	DynamicJsonDocument doc(2014);
	deserializeJson(doc, jdata); // json string from client
	
    JsonObject root = doc.as<JsonObject>();
    int idx=-1;

    // using C++11 syntax (preferred):
for (JsonPair kv : root) {
    for (int i=0;i<WS_client_type_array_len;i++)
  		if(strcmp(kv.key().c_str(),WS_client_type_array[i])==0) 
        {
            idx=i; 
            break; };
    Serial.println(kv.key().c_str());
    Serial.println(kv.value().as<char*>());
}

/*
	JsonObject root = doc.as<JsonObject>();

	JsonObject::iterator it=root.begin();

	int idx=-1;
    
	for (int i=0;i<WS_client_type_array_len;i++)
  		if(strcmp(it.key().c_str()),WS_client_type_array[i])==0) 
        {
            idx=i; 
            break; };
*/

	switch(idx){
		case SET_REF:// SET_REF websocket message type
			RefADC=CurrADC; 
			ws.textAll("SET_REF_OK");
			break;
		case SET_BASE :// SET_BASE websocket message tpye
		   BaseADC=CurrADC; 
		   ws.textAll("SET_BASE_OK");
			break;
		case SET_REFKG:// SET_REFKG websocket message type 
		   RefKG=it.value().as<float>();            
		   ws.textAll("SET_REFKG_OK");
			break;
		case SET_UXTIME:
			break;
		default: 
			break;
	}
}

void onWebsocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
    void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", 
                client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;
        case WS_EVT_DATA:
            //handleClientWebSocketMessage(arg, data, len);
	    handleClientWebSocketMessage(data);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
        break;
    }
}

void webSocket_init() {
    ws.onEvent(onWebsocketEvent);
    server.addHandler(&ws);
}

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void ntpClient_init(){
    timeClient.begin();
    timeClient.update();
}

void esp8266_init(){
    fs_init();
    wifi_init(WIFI_AP_STA); // or WIFI_AP
    webserver_init();
    webSocket_init();
    ntpClient_init();
}
