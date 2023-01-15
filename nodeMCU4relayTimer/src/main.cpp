#include <Arduino.h>
#include "init.h"

float prevMarker, nextMarker;

void pins_init(){
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(BUILTIN_LED, OUTPUT);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

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