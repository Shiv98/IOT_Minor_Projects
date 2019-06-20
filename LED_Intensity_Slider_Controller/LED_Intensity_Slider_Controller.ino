#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

const char ssid[20] = "68";
const char password[20] = "qwertyuiop";
int led1 = D1;
int led2= D2;



WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);
    
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
 

    delay(500);
    Serial.println("");
    Serial.println("Server-------------------------------");
    Serial.print("Configuring access point");
    WiFi.mode(WIFI_AP);           
    WiFi.softAP(ssid, password);
    //WiFi.begin(ssid, password);

    Serial.println("");
    Serial.print("Hotspot Created : ");
    Serial.println(WiFi.softAPIP());

  // Start the server
    server.begin();
    Serial.println("Server started");
    Serial.println("-------------------------------------");
    Serial.println("");
    Serial.println(WiFi.localIP());

 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  server.begin();                  //Start server
  Serial.print("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
int idx,val;
String sub;
void loop(void){
//Handle client requests
WiFiClient client = server.available();
if(!client)
return;

while(!client.available())
delay(1);

String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

idx= request.indexOf("-");

sub = request.substring(idx+1);
val = sub.toInt();
Serial.println(sub);
if(request.indexOf("S1")!=-1){
  
  analogWrite(D2,val);
  }
  if(request.indexOf("S2")!=-1){
  
  analogWrite(D1,val);
  }
// server.handleClient();

}
