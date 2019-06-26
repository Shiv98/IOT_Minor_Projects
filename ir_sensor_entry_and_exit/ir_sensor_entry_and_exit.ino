#include <ESP8266WiFi.h>

const char ssid[20] = "S9";
const char password[20] = "iotkanpur";
int ir1 = D1;
int ir2= D2;
int count=0;
WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);
    
    pinMode(ir1, INPUT);
    pinMode(ir2, INPUT);

    
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
    int value = digitalRead(ir1);
    int value1=digitalRead(ir2);
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("Count of: ");
    if(value == LOW )
    {
    Serial.println(value);
    count=count+1;
    }
    else if(value1== LOW)
    {
    Serial.println(value1);
    count=count-1;
    }
    client.println("<br><br>");
    client.println(count);
    client.println("</html>");
    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");
}
