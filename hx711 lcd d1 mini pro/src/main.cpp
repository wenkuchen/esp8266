#include <Arduino.h>
#include "init.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h" 

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

void setup() {
  Serial.begin(115200);
  esp8266_init();
	delay(20);
  
  lcd.init(); // initialize the lcd 
  lcd.backlight();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
}