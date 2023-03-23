#include <FirebaseESP32.h>
#include "WiFi.h"
#define WIFI_SSID "speed"
#define WIFI_PASSWORD "18678a20"
#define FIREBASE_HOST "https://smart-heater-5c59e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "9oCyU1KMSmRqhnNli9YqURg4zZ1a6WJWuZ3VoYpi"
FirebaseData fbdo;
FirebaseData getdata1;
FirebaseJson json;
String tempH="",tempR="",smokeH="",smokeR="",pres="",TIME="";
int d=0;
String saj="";
String h="1";
String h1="2";
String h2="3";

String d1="";
String d2="";
String d3="";
int a=0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
pinMode(19,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  digitalWrite(19,HIGH);
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

//      Firebase.setString(fbdo, "/tempH", "0");
//      Firebase.setString(fbdo, "/tempR", "0");
//      Firebase.setString(fbdo, "/pres", "0");
//      Firebase.setString(fbdo, "/smokeH", "0");
//      Firebase.setString(fbdo, "/smokeR", "0");
//      Firebase.setString(fbdo, "/TIME", "0");
  
}
void loop(){
  Firebase.getString(getdata1,"Fan");
  d1=getdata1.stringData();
  Serial.println(d1);
   if(d1==String(1)){
    digitalWrite(23,LOW);
   }
   else{
   digitalWrite(23,HIGH);}
  Firebase.getString(getdata1,"Heater");
  d2=getdata1.stringData();
  Serial.println(d2);
     if(d2==String(1)){
    digitalWrite(22,LOW);
    if(a==0){
    digitalWrite(19,LOW);
    delay(3000);
    digitalWrite(19,HIGH);
    a=1;
    }
   }
   else{
    a=0;
   digitalWrite(22,HIGH);
   digitalWrite(19,HIGH);
   }
  Firebase.getString(getdata1,"case");
  d3=getdata1.stringData();
  Serial.println(d3);
if(Serial2.available()>0)
  {
        saj=Serial2.readStringUntil('$');
        Serial.println(saj);
        
       for(int i=0;i<saj.length();i++)
       {
        char f1=saj[i];
        
        if(f1==':')
        {
          d=d+1;
          }
         if(d==0)
         {
          tempH+=saj[i];
          }
         else if(d==1)
         {
          tempR+=saj[i];
          
          }
         else if(d==2)
         {
          pres+=saj[i];
          }
         else if(d==3)
         {
          smokeH+=saj[i];
          }
         else if(d==4)
         {
          smokeR+=saj[i];
          }
          else if(d==5)
         {
          TIME+=saj[i];
          }
          
        }
        saj="";
       // Serial.println(tempR);Serial.println(tempH); Serial.println(pres); Serial.println(smokeH);Serial.println(smokeR);Serial.println(TIME);
           
  
    tempR=tempR.substring(1,tempR.length());
    pres=pres.substring(1,pres.length());
    smokeH=smokeH.substring(1,smokeH.length());
    smokeR=smokeR.substring(1,smokeR.length());
    TIME=TIME.substring(1,TIME.length());
    if(tempR.length()>=1 && tempH.length()>=1 && pres.length()>=1 && smokeH.length()>=1 && smokeR.length()>=1 && TIME.length()>=1)
    {
      if(tempR.toInt()>1&&tempR.toInt()<35){
        Firebase.setInt(fbdo, "/hh", h.toInt());
      }
      else if (tempR.toInt()>36&&tempR.toInt()<66){
       Firebase.setInt(fbdo, "/hh", h1.toInt());

      }
      else if (tempR.toInt()>67&&tempR.toInt()<100){
       Firebase.setInt(fbdo, "/hh", h2.toInt());
      }


      if(tempH.toInt()>1&&tempH.toInt()<35){
        Firebase.setInt(fbdo, "/hh2", h.toInt());
      }
      else if (tempH.toInt()>36&&tempH.toInt()<66){
       Firebase.setInt(fbdo, "/hh2", h1.toInt());

      }
      else if (tempH.toInt()>67&&tempH.toInt()<100){
       Firebase.setInt(fbdo, "/hh2", h2.toInt());
      }
//   if(smokeH.toInt()==0){
//    digitalWrite(23,HIGH);
//    digitalWrite(22,LOW);
//   }
//   if(smokeR.toInt()==0){
//    digitalWrite(35,HIGH);
//    digitalWrite(36,LOW);
//   }
  //  Serial.println(tempR);Serial.println(tempH); Serial.println(pres); Serial.println(smokeH);Serial.println(smokeR);Serial.println(TIME);
    Firebase.setInt(fbdo, "/tempH", tempH.toInt());
    Firebase.setInt(fbdo, "/tempR", tempR.toInt());
    Firebase.setInt(fbdo, "/pres", pres.toInt());
    Firebase.setInt(fbdo, "/smokeH", smokeH.toInt());
    Firebase.setInt(fbdo, "/smokeR", smokeR.toInt());
    Firebase.setInt(fbdo, "/TIME", TIME.toInt());
      }
 }
tempH="";

tempR="";
smokeH="";
smokeR="";
pres="";
TIME="";
saj="";
d=0;
Serial.println(".............");

  
}
