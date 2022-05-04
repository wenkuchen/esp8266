#include <Arduino.h>
#include "config.h"
#include "init.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h" 

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

void LcdMsgLine(int col, int row, String msg){ 
  lcd.setCursor(0,row);
  lcd.print("                "); // clear the row
  lcd.setCursor(col,row);
  lcd.println(msg);   
}

void setup() {
  Serial.begin(115200);
  esp8266_init();
	delay(20);
  
  lcd.init(); // initialize the lcd 
  lcd.backlight();lcd.clear();
  LcdMsgLine(2,0, "Scale Ready   ");
  LcdMsgLine(1,1, WiFi.localIP().toString().c_str());

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
}