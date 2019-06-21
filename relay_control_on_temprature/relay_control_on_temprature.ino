#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

const char ssid[20] = "team__68";
const char password[20] = "qwertyuiop";
int ht = A0;
int relay = D5;

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
     //baud rate for serial monitor
    pinMode(ht, INPUT);
    pinMode(D2, OUTPUT);
    pinMode(D5, OUTPUT);
    digitalWrite(relay,LOW);
    delay(5000);
    
    Serial.println("");
    Serial.println("Server-------------------------------");
    Serial.print("Configuring access point");
    //WiFi.mode(WIFI_AP);           
    //WiFi.softAP(ssid, password);
    WiFi.begin(ssid, password);
    while(WiFi.status()!=WL_CONNECTED)
    {
      Serial.print(".");
      delay(100);
    }
    Serial.println("");
    server.begin();
    Serial.print("Hotspot Created : ");
    //Serial.println(WiFi.softAPIP());
    Serial.print("http://");
    Serial.println(WiFi.localIP());
    Serial.println("/");
  // Start the server
    
    Serial.println("Server started");
    Serial.println("-------------------------------------");
    Serial.println("");
}
void loop() {
// Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
// Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
      delay(1);
    }
// Match the request 
    float value = analogRead(ht);
    float temp1 = (value/1024.0)*5000;
    float temperature = temp1/10;

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    int values = LOW;
    if (request.indexOf("/ON1") != -1) {
      digitalWrite(relay, HIGH);
      values = HIGH;
    }
    if (request.indexOf("/OFF1") != -1) {
      digitalWrite(relay, LOW);
      values = LOW;
    }
    
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("Temperature is: ");
    client.println("<br><br>");
    client.println(temperature);

    
    client.print("Relay is now: ");
    if(values == HIGH) {
    client.print("On");
    } else {
    client.print("Off");
    }
    client.println("<br><br>");
    client.println("<a href=\"/ON1\"\"><button>On </button></a>");
    client.println("<a href=\"/OFF1\"\"><button>Off </button></a><br />");
    client.println("</html>");
    
    
    
    client.println("</html>");
    delay(1);
    
    if(temperature >  18 )
    {                                                            
    Serial.println(temperature);
    digitalWrite(D2,HIGH);
    }
    else if(temperature <= 18)
    {
    Serial.println(temperature);
    digitalWrite(D2,LOW);
    }

 
    Serial.println("Client disonnected");
    Serial.println("");
}
