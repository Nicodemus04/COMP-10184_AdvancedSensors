// ****************************************************************** 
//I, Nicodemus Allan, student number 000838957, certify that this material is my original work. No other person's work has been used without due acknowledgment and I have not made my work available to anyone else.
//
//Date: 2022-10-03
 
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

//initialising deviceAddress
DeviceAddress deviceAddress;


void printAddress(DeviceAddress deviceAddress) {
  //loops through the adress values and prints them out
  for (int i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  Serial.println("Tempurature Aplication");
  if (DS18B20.getAddress(deviceAddress, 0))
  {
    Serial.print("Found DS18B20 sensor with address: ");
    //calls method to print address out
    printAddress(deviceAddress);
  }
  else{
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
} 

//checks the temperature and prints apropriate response
String checkTemp(float fTemp)
{
  if (fTemp > 35)
  {
    return "Too Hot!";
  }
  else if (fTemp >= 30)
  {
    return "Hot";
  }
  else if (fTemp >= 25)
  {
    return "Warm";
  }
  else if (fTemp >= 15)
  {
    return "Perfect";
  }
  else if (fTemp >= 10)
  {
    return "Cool";
  }
  else
  {
    return "Cold!";
  }
}

void loop() { 
  //checks if sensor is connected
  if (DS18B20.getAddress(deviceAddress, 0))
  {
    float fTemp; 
    
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0); 
    
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + checkTemp(fTemp)); 
  
    // wait 5s (5000ms) before doing this again
    delay(5000); 
  }
} 

