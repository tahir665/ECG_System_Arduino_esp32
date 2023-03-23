//#include <SoftwareSerial.h>
#include <TinyGPS.h>
 
long lat,lon; // create variable for latitude and longitude object
 
//SoftwareSerial gpsSerial(2, 3); // create gps sensor connection
TinyGPS gps; // create gps object

                       
void setup(){

  //gpsSerial3.begin(4800); // connect gps sensor
  Serial.begin(115200);
}
 
void loop(){

  while(Serial.available()>0){ // check for gps data
  // Serial.print("fakhar");
   gps.encode(Serial.read()); // encode gps data
   //Serial.print(gps.encode(Serial3.read()));
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
    Serial.print("Position: ");
    Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(lon); // print longitude
   
  }
}
