#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

const char ssid[20] = "S9";
const char password[20] = "qwertyuiop";
int red = D1;
int green = D3;
int blue = D2;

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
     //baud rate for serial monitor
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
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
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    //int values = HIGH;
    if (request.indexOf("/R") != -1) {
      digitalWrite(red, LOW); 
      digitalWrite(green, HIGH);
      digitalWrite(blue, HIGH);
      //values = HIGH;
    }
    if (request.indexOf("/G") != -1) {
      digitalWrite(blue, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      //values = HIGH;
    }
    if (request.indexOf("/B") != -1) {
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
      //values = HIGH;
    }
    if (request.indexOf("/O") != -1) {
      digitalWrite(green, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
      //values = HIGH;
    }
    if (request.indexOf("/W") != -1) {
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      //values = HIGH;
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    
    client.println("<br><br>");
    client.println("<a href=\"/R\"\"><button>Red</button></a>");
    client.println("<a href=\"/G\"\"><button>Green</button></a><br />");
    client.println("<a href=\"/B\"\"><button>Blue</button></a><br />");
    client.println("<a href=\"/W\"\"><button>White</button></a><br />");
    client.println("<a href=\"/O\"\"><button>None</button></a><br />");

    
    client.println("</html>");
    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");
}
