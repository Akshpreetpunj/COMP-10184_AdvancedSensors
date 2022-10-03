/* I Akshpreet Singh Punj, 000820040 certify that this material is my original work. 
  No other person's work has been used without due acknowledgement. 
  I have not made my work available to anyone else.
*/
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

// declaring a Byte buffer for holding the ID of the DS18B20 sensor
uint8_t address[8];

// Checking the sensor status, whether it is attached or not (DS18B20)
bool sensorStatus = false;

void setup() { 
  uint8_t address[8];

  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  Serial.println("\nTemperature Application");

  // Checking the sensor status (DS18B20) and printing the sensor ID 
  if(DS18B20.getAddress(address, 0)){
    Serial.print("Found DS18B20 sensor with address: ");
    sensorStatus = true;
  } else {
    Serial.println("No DS18B20 temperature sensors are installed!");
    sensorStatus = false;
    return;
  }

  // printing each byte of the DS18B20 address in hexadecimal format
  for(int i = 0; i < 8; i++){
    Serial.printf("%02X", address[i]);
  }
  Serial.println("");
} 
 
void loop() { 
  // Checking if the DS18B20 sensor is attached
  if(sensorStatus == true) {
    float fTemp;

    // variable for temperature judgement
    String judgement = ""; 
  
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0); 

    // Checking the temperature value and assigning the judgement value according to the temperature
    if(fTemp < 10){
      judgement = "Cold!";
    } else if (fTemp >= 10 && fTemp < 15){
      judgement = "Cool";
    } else if (fTemp >= 15 && fTemp < 25){
      judgement = "Perfect";
    } else if (fTemp >= 25 && fTemp < 30){
      judgement = "Warm";
    } else if (fTemp >= 30 && fTemp < 35){
      judgement = "Hot";
    } else if (fTemp >= 35) {
      judgement = "Too Hot!";
    }
  
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + judgement); 
  
    // wait 5s (5000ms) before doing this again 
    delay(5000);
  } 
}