
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


#define DS18B20 A14
#define REPORTING_PERIOD_MS     1000

float temperature, humidity, BPM, SpO2, bodytemperature;

/*Put your SSID & Password*/


PulseOximeter pox;

uint32_t tsLastReport = 0;
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
const int rs = 12, en = 13, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
//const int pulsewire=A8;
String tx_u="";
int TEMP;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <TinyGPS.h>
#include <SoftwareSerial.h>
//static const int RXPin = 0, TXPin = 1;

// The serial connection to the GPS device
TinyGPS gps;
int g_en=0;
int r_chk=0;
String incoming = ""; 
String gps_data="";
String gps_data_1="";
String gps_data_2="";
String get_lon="";
String get_lat="";
String lon_="";
String lat_="";
double lat;
double lon;


int temp=0;
void onBeatDetected()
{
  //Serial.println("Beat!");
  temp=temp+2;
}
void(* resetFunc) (void) = 0;
void setup() {
  Serial3.begin(GPSBaud);
  Serial.begin(115200);
  Serial1.begin(115200);
 // Serial1.begin(115200);
  lcd.begin(20, 4);
 

 // Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
  //  Serial.println("FAILED");
    for (;;);
  } else {
  // Serial.println("SUCCESS");
    pox.setOnBeatDetectedCallback(onBeatDetected);
  }
  
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  // Register a callback for the beat detection
 Serial3.begin(GPSBaud);
  

Serial2.begin(19200);
  // Give time to your GSM shield log on to network
 // delay(2000);   
  //Serial.begin(9600);
  // Send the SMS
 // Serial.println("Start0");
 // sendSMS();
 pinMode(25,OUTPUT);
}
void loop() {
String a;
  






  
  pox.update();


  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  { 
    BPM = pox.getHeartRate();
    lcd.setCursor(0,0);
     lcd.print("BPM: ");
    lcd.print(BPM);
    //Serial.print("BPM: ");
    //Serial.println(BPM);
    if(BPM>150){
      senddata();
      digitalWrite(25,HIGH);
      delay(1000);
      digitalWrite(25,LOW);
      sendSMS();
      resetFunc();
    }
    SpO2 = pox.getSpO2();
    lcd.setCursor(0,1);
    //Serial.print("SpO2: ");
    //Serial.print(SpO2);
    //Serial.println("%");
    lcd.print("SpO2: ");
    lcd.print(SpO2);
    bodytemperature = sensors.getTempCByIndex(0);
    lcd.setCursor(0,2);
    //Serial.print("Body Temperature: ");
    //Serial.print(bodytemperature);
    //Serial.println("°C");
    lcd.print("Temperature:");
    lcd.print(bodytemperature);
    lcd.setCursor(0, 3);
    lcd.print("ECG:");
if((digitalRead(6) == 1)||(digitalRead(7) == 1)){
  lcd.setCursor(0, 3);
  lcd.print("ECG:");
  //Serial.println('!');
  }
   lcd.print(analogRead(A0));
   senddata();
  

    
    
    //Serial.println("*********************************");
    //Serial.println();
    //senddata();
    if (temp%8==0){
    sensors.requestTemperatures();
    

  }
  if (temp==100){
    temp=0;
  }
//  senddata();
    
    tsLastReport = millis();
    
  }
//senddata();
while (Serial3.available() > 0){
    char get_data=Serial3.read();
    //Serial.print(get_data);
    if(get_data=='$')
    {
      g_en=1;
      gps_data="";
      gps_data_2="";
      }
    if(g_en==1)
    {
      gps_data+=get_data;
      if(gps_data.length()==6 && gps_data=="$GNGLL")
      {
        //Serial.println(gps_data);
        //Serial.println("...........");
        g_en=2;
        
        }
       
     
      }
     else if(g_en==2)
     {
      gps_data_2+=get_data;
     
      
      }
    
    //Serial.println(gps_data_2);
   // Serial.println("...........");
   // Serial.println(incoming);  
  }

 if(gps_data_2.length()>30)
   {
   // Serial.println(gps_data_2);
    for(int i=0;i<gps_data_2.length();i++)
    {
      //Serial.println(gps_data_2[i]);
      if(gps_data_2[i]==',')
      {
        r_chk++;
      }
        if(r_chk==1)
        {
          
          get_lat+=gps_data_2[i];
          }
         else if(r_chk==3)
         {
        
          get_lon+=gps_data_2[i];
          }
        
      }
      r_chk=0;
      get_lat=get_lat.substring(1,get_lat.length());
      float lat=get_lat.toFloat()/100.00000;
       //long checkit = (long) (lat * 10000.0) ;
      
       
       float lat2_ =lat-int(lat);
       float lat2__=lat2_*100;
       float lat2_1=(lat2__/60)+int(lat);
       
       
      lat_=String(lat2_1,7);
      



      get_lon=get_lon.substring(2,get_lon.length());
    float lon=get_lon.toFloat()/100.00000;
       //long checkit = (long) (lat * 10000.0) ;
      
       
       float lon2_ =lon-int(lon);
       float lon2__=lon2_*100;
       float lon2_1=(lon2__/60)+int(lon);
       
       
       lon_=String(lon2_1,7);
      
    gps_data_2="";
    get_lat="";
    get_lon="";

    
    
    }
}
void senddata(){
   //making data in the form of string for wifimodule// 
tx_u+=String(BPM);
tx_u+=':';
tx_u+=String(analogRead(A0));
tx_u+=':';
tx_u+=String(bodytemperature);
tx_u+=':';
tx_u+=String(SpO2);
tx_u+=':';
tx_u+=lat_;
tx_u+=':';
tx_u+=lon_;
tx_u+='$';
Serial1.println(tx_u);
Serial.println(tx_u);
tx_u="";

}
void sendSMS() {
  // AT command to set SIM900 to SMS mode
   
Serial2.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
 
Serial2.println("AT + CMGS = \"+923408023536\"");
  delay(100);
  
  // SMS MESSAGE CONTENT
Serial2.println("patient need treatment");
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial2.println((char)26); 
  delay(100);

  Serial2.println();
  // Give module time to send SMS
  delay(5000); 
}
