#include <Arduino.h>
#include <math.h>
#include <Wire.h>

#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;

#include <OneWire.h> 

/********************************************************************/
//library of temperature sensor
#include <DallasTemperature.h> 

/********************************************************************/
//library of Lcd                        
#include <LiquidCrystal.h>  

/********************************************************************/
/// Data wire is plugged into pin 53 on the Arduino 
#define ONE_WIRE_BUS A14      

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
OneWire oneWire(ONE_WIRE_BUS);

/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/********************************************************************/ 
       ///define pins and variables////  
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
//const int pulsewire=A8;
String tx_u="";
int TEMP;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float temperature, humidity, BPM, SpO2, bodytemperature;
 
int temp=0;
void onBeatDetected()
{
  Serial.println("Beat!");
  temp=temp+2;
}
 
void setup()
{
    Serial.begin(9600);
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     //pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
    lcd.begin(20, 4);
    sensors.begin(); 
     Serial2.begin(19200);
  // Give time to your GSM shield log on to network
 // delay(2000);   
  //Serial.begin(9600);
  // Send the SMS
  Serial.println("Start0");
//  sendSMS();
}
 
void loop()
{
    // Make sure to call update as fast as possible




pox.update();

  //sensors.requestTemperatures();
  //BPM = pox.getHeartRate();
  //SpO2 = pox.getSpO2();
  //bodytemperature = sensors.getTempCByIndex(0);


  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  { 
    BPM = pox.getHeartRate();
    lcd.setCursor(0,0);
    Serial.print("BPM: ");
    lcd.print("BPM: ");
    lcd.print(BPM);
    Serial.println(BPM);
    SpO2 = pox.getSpO2();
    lcd.setCursor(0,1);
    Serial.print("SpO2: ");
    Serial.print(SpO2);
    Serial.println("%");
    lcd.print("SpO2: ");
    lcd.print(SpO2);
    lcd.print("%");
    bodytemperature = sensors.getTempCByIndex(0);
    lcd.setCursor(0,2);
    Serial.print("Body Temperature: ");
    Serial.print(bodytemperature);
    Serial.println("°C");
    lcd.print("Temperature: ");
    lcd.print(bodytemperature);

    Serial.println("*********************************");
    Serial.println();
    if (temp%8==0){
    sensors.requestTemperatures();

  }
  if (temp==100){
    temp=0;
  }
    
    tsLastReport = millis();
    
  }


    
}
