
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#include <LiquidCrystal_I2C.h>


// Our configuration structure.
//
// Never use a JsonDocument to store the configuration!
// A JsonDocument is *not* a permanent storage; it's only a temporary storage
// used during the serialization phase. See:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/

struct Config {
  char hostname[64];
  int port;
};

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

const char *filename = "/config.txt";  // <- LittleFS library uses 8.3 filenames
Config config;                         // <- global configuration object

// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
  File file = LittleFS.open(filename,"R");

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
    config.port = doc["port"] | 2731;
    strcpy(config.hostname,                  // <- destination
          doc["hostname"] | "example.com"  // <- source
          );    

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config) {
  // Delete existing file, otherwise the configuration is appended to the file
  LittleFS.remove(filename);

  // Open file for writing
  File file = LittleFS.open(filename, "W");
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["hostname"] = config.hostname;
  doc["port"] = config.port;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = LittleFS.open(filename,"R");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize LittleFS library
  while (!LittleFS.begin()) {
    Serial.println(F("Failed to initialize LittleFS library"));
    delay(1000);
  }

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadConfiguration(filename, config);

  // Create configuration file
  Serial.println(F("Saving configuration..."));
  saveConfiguration(filename, config);

  // Dump config file
  Serial.println(F("Print config file..."));
  printFile(filename);
}

void readData()
{
   //Open the file
   File file = LittleFS.open("/SavedFile.txt", "r");
  //Check if the file exists
   if(!file){
   //Read the file data and display it on LCD
    Serial.println("No Saved Data!");
    lcd.clear();
    lcd.print("No Saved Data!");   
    return;
   }
      lcd.clear();
      lcd.print("Saved Data :");
      // set cursor to first column, second row
      lcd.setCursor(0,1);
      //Display on the LCD
      while(file.available()){
      lcd.write(file.read());
      }   
      //reset cursor poisition
      lcd.setCursor(0,0);
   //Close the file
    file.close();
}
void writeData(String data)
{
  //Open the file 
  File file = LittleFS.open("/SavedFile.txt", "w");
  //Write to the file
  file.print(data);
  //Close the file
  file.close();
  delay(1); 
  Serial.println("Write successful");
  lcd.clear();
  lcd.print("Data Saved :"); 
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  // print the data on the LCD
  lcd.print(data);
  // reset cursor position
  lcd.setCursor(0,0);
}
void deleteData()
{
   //Remove the file
   LittleFS.remove("/SavedFile.txt"); 
   lcd.clear();
   lcd.print("Data Deleted"); 
}