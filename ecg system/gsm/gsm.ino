/*********
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <SoftwareSerial.h>

// Configure software serial port
//SoftwareSerial SIM900(2, 3); 

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  Serial3.begin(19200);
  // Give time to your GSM shield log on to network
  delay(2000);   
  Serial.begin(9600);
  // Send the SMS
  Serial.println("Start0");
 // sendSMS();
  
}

void loop() { 
  delay(5000);   
//  if (Serial3.available()>0){
//
//    Serial.write(Serial3.read());
//  }
//  Serial3.println("AT");
//  delay(1000);
//  Serial3.println("AT+GSN");
//  delay(1000);
  // Send the SM
  sendSMS();
  
}

void sendSMS() {
  // AT command to set SIM900 to SMS mode
  Serial.print("tahir");
  Serial3.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  Serial.print("tahir1");
  Serial3.println("AT + CMGS = \"+923155018656\""); 
  delay(100);
  Serial3.println("AT+CGSN");
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  Serial.print("tahir2");
  Serial3.println("Message example from Arduino"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial3.println((char)26); 
  delay(100);
  Serial3.println();
  // Give module time to send SMS
  delay(5000); 
}
