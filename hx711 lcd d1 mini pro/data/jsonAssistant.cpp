#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

StaticJsonDocument<768> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

JsonObject scale = doc["scale"];
int scale_CurrADC = scale["CurrADC"]; // 0
int scale_BaseADC = scale["BaseADC"]; // 0
int scale_RefADC = scale["RefADC"]; // 0
int scale_RefKG = scale["RefKG"]; // 2

JsonObject config = doc["config"];
const char* config_VERSION = config["VERSION"]; // "2.0.1"
const char* config_LastModified = config["LastModified"]; // "2022/05/22"
const char* config_FileName = config["FileName"]; // "hx711LcdScale.cpp"
const char* config_hostname = config["hostname"]; // "scale.local"
const char* config_ap_ssid = config["ap_ssid"]; // "scale_espd1"
const char* config_ap_pswd = config["ap_pswd"]; // "23752755"
const char* config_sta_ssid = config["sta_ssid"]; // "WKC"
const char* config_sta_spswd = config["sta_spswd"]; // "23752755"

JsonObject wsClient_msgType = doc["wsClient_msgType"];
int wsClient_msgType_SET_REF = wsClient_msgType["SET_REF"]; // 0
int wsClient_msgType_SET_REFKG = wsClient_msgType["SET_REFKG"]; // 1
int wsClient_msgType_SET_BASE = wsClient_msgType["SET_BASE"]; // 2
int wsClient_msgType_UPDATE_UXTIME = wsClient_msgType["UPDATE_UXTIME"]; // 3

JsonObject wsServer_msgType = doc["wsServer_msgType"];
int wsServer_msgType_ON_CHANGE = wsServer_msgType["ON_CHANGE"]; // 0
int wsServer_msgType_SET_REF_OK = wsServer_msgType["SET_REF_OK"]; // 1
int wsServer_msgType_SET_REFKG_OK = wsServer_msgType["SET_REFKG_OK"]; // 2
int wsServer_msgType_SET_BASE_OK = wsServer_msgType["SET_BASE_OK"]; //