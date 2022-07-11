#include <Arduino.h>
#include <ArduinoJson.h>

/* Json content
{
    "sensor": "gps",
    "time": 1542569854,
    "data": [
        48.26524,
        120.2514
    ]
}
*/

char* PosJson = "{\"sensor\":\"gps\",\"time\":1542569854,\"data\":[48.26524,120.2514]}";

//StaticJsonBuffer<256> jsonBuffer;ˊ
StaticJsonBuffer <200> JsonBuffer;
JsonObject& root = JsonBuffer.parseObject(PosJson);

if(!root.success()) {
    Serial.println("Error");
    break;
}