#include <Arduino.h>
#include "init.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp_init();
	delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
}