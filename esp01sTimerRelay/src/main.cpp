#include <Arduino.h>
#include "config.h"
#include "init.h"

#define RELAY_PIN 3

float prevMarker, nextMarker;

void pins_init(){
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUILTIN_LED, HIGH);
}

void setTimerMarker(char* timerMarkerString){

}

void RunTimer() {
  // get current time
  // if current time reaches the next hour marker, 
  // toggle relay status
}

void setup() {

  esp8266_init();
  pins_init();

  //set Unix time when Wifi or websocke connected
}

void loop() {
  // put your main code here, to run repeatedly:
  RunTimer();
}