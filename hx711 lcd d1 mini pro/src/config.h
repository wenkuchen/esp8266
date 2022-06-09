#ifndef CONFIG_H
#define CONFIG_H
/*
 * This example demonstrate how to use asynchronous client & server APIs
 * in order to establish tcp socket connections in client server manner.
 * server is running (on port 7050) on one ESP, acts as AP, and other clients running on
 * remaining ESPs acts as STAs. after connection establishment between server and clients
 * there is a simple message transfer in every 2s. clients connect to server via it's host name
 * (in this case 'esp_server') with help of DNS service running on server side.
 *
 * Note: default MSS for ESPAsyncTCP is 536 byte and defualt ACK timeout is 5s.
*/

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#endif

#define DEF_SSID "WKC"
#define DEF_PASSWORD "23752755"

#define SERVER_HOST_NAME "scale_server"

#define TCP_PORT 7050
#define DNS_PORT 53

#endif // CONFIG_H
