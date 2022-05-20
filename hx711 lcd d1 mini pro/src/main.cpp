#include <Arduino.h>
#include "config.h"
#include "init.h"
#include <LiquidCrystal_I2C.h>
#include "HX711.h" 

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale; // init HX711 scale

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

void LcdMsgLine(int col, int row, String msg){ 
  lcd.setCursor(0,row);
  lcd.print("                "); // clear the row
  lcd.setCursor(col,row);
  lcd.println(msg);   
}
/**
void setup() {
  Serial.begin(115200);
  scale.begin(DT_PIN, SCK_PIN);
  scale.set_scale();  // 開始取得比例參數
  scale.tare();
  Serial.println("Nothing on it.");
  Serial.println(scale.get_units(10));
  Serial.println("Please put sapmple object on it..."); //提示放上基準物品
  
}

void loop() {
  float current_weight=scale.get_units(10);  // 取得10次數值的平均
  float scale_factor=(current_weight/sample_weight);
  Serial.print("Scale number:  ");
  Serial.println(scale_factor,0);  // 顯示比例參數，記起來，以便用在正式的程式中
  
}
**/
void setup() {
  Serial.begin(115200);
  esp8266_init();
	delay(20);
  
  lcd.init(); // initialize the lcd 
  lcd.backlight();lcd.clear();
  LcdMsgLine(2,0, "Scale Ready   ");
  LcdMsgLine(1,1, WiFi.localIP().toString().c_str());

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

Serial.println("Before setting up the scale:");
Serial.print("read: \t\t");
Serial.println(scale.read()); // print a raw reading from the ADC

Serial.print("read average: \t\t");
Serial.println(scale.read_average(20)); 
// print the average of 20 readings from the ADC

Serial.print("get value: \t\t");
Serial.println(scale.get_value(5)); 
// print the average of 5 readings from the ADC minus the tare weight (not set yet)

Serial.print("get units: \t\t");
Serial.println(scale.get_units(5), 1); 
// print the average of 5 readings from the ADC minus tare weight (not set) divided
// by the SCALE parameter (not set yet)

scale.set_scale(2280.f); 
// this value is obtained by calibrating the scale with known weights; 
// see the README for details
scale.tare(); // reset the scale to 0

Serial.println("After setting up the scale:");

Serial.print("read: \t\t");
Serial.println(scale.read()); // print a raw reading from the ADC

Serial.print("read average: \t\t");
Serial.println(scale.read_average(20)); 
// print the average of 20 readings from the ADC

Serial.print("get value: \t\t");
Serial.println(scale.get_value(5)); 
// print the average of 5 readings from the ADC minus the tare weight, set with tare()

Serial.print("get units: \t\t");
Serial.println(scale.get_units(5), 1); 
// print the average of 5 readings from the ADC minus tare weight, divided
// by the SCALE parameter set with set_scale

Serial.println("Readings:");

}

void loop() {
Serial.print("one reading:\t");
Serial.print(scale.get_units(), 1);
Serial.print("\t| average:\t");
Serial.println(scale.get_units(10), 1);

}
