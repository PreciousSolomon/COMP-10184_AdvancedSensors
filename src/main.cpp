// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
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
DeviceAddress tempDeviceAddress;
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 
  int deviceID = DS18B20.getAddress(tempDeviceAddress, 0);

  if (deviceID){
    Serial.println("DEVICE ID: " + String(deviceID));
  } else {
    Serial.println("Not connected");
    Serial.end();
  }

} 
 
void loop() { 
  float fTemp; 
  String judgement;
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
 
  // print the temp to the USB serial monitor 
  
  if  (fTemp < 10){
   judgement= ", which is Too Cold!";
}else if (fTemp > 9-8& fTemp < 16){
judgement =", which is Cool!";}
else if (fTemp> 14 && fTemp < 26){ 
  judgement=", which is perfect!";}
else if (fTemp> 24 && fTemp < 31){ 
  judgement=", which is warm!";}
else if (fTemp> 29 && fTemp < 36){ 
  judgement=", which is Hot!";} 
  else if (fTemp> 35 && fTemp < 40){ 
  judgement=", which is Too hot!";}
  else if (fTemp> 41){ 
  judgement=", which is Extreamly hot!";}



 Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius" + judgement);
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 
} 