#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
//static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;
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
String get_lat_1="";
String get_lat_2="";
String get_lat_3="";
float lat;
float lon;
int a;
int b;
int d=0;
//SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  Serial3.begin(GPSBaud);
  Serial.begin(9600);
//  ss.begin(GPSBaud);
}
void loop()
{
  //bool newData = false;
  //unsigned long chars;
//  unsigned short sentences, failed;
  // Output raw GPS data to the serial monitor
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
      lat=get_lat.toFloat();
      lat=lat/100;
      
   
      Serial.println(lat,5);



      get_lon=get_lon.substring(2,get_lon.length());
      lon=get_lon.toFloat();
      lon=lon/100;
      Serial.println(lon,5);
       
      Serial.println(",,,,,,,,,,,,,,,,,");
    gps_data_2="";
    get_lat="";
    get_lon="";

    
    
    }




}
