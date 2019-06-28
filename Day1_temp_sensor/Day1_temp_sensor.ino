#include "ThingSpeak.h"

#include <ESP8266WiFi.h>

char ssid[] = "rpi68";   // your network SSID (name) 
char pass[] = "HS360000";
;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 808067;
const char * myWriteAPIKey = "T8SUXQ3IUKP7YS4Z";

int number = 0;

float temp;
int tempPin = 0;


void setup() {
  Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("yashika0998");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // change the value
   temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp=((temp*3.3/1023)*100);
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*C");
   Serial.println();
   delay(1000); // update sensor reading each one second
  
  delay(20000); // Wait 20 seconds to update the channel again
}
