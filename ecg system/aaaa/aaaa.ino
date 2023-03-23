#include <SoftwareSerial.h>

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
//SoftwareSerial ss(4, 3);

void setup()
{
  Serial.begin(115200);
  Serial3.begin(9600);
  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
}
int ind=0;
String a;
String b;
int checkb=0;
void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  
  

  // For one second we parse GPS data and report some key values

    while (Serial3.available())
    {
      
      char c = Serial3.read();
       //Serial.write(c);
       if(ind<7){
        a+=c;
        ind++;
       }
       
       if(a=="$GNGLL,"){
        checkb=1;
        // uncomment this line if you want to see the GPS data flowing
        
        
       }
       if (ind==7){
        
       a="";
       ind=0; 
       }
       if (checkb>0){
        b+=c;
        
        checkb++;
        if(checkb>10 && c==','){
        Serial.println(b);
        b="";
        checkb=0;  
        }
       
        
       }
 
}}
