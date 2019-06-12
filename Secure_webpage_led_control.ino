#include <ESP8266WiFi.h>

const char ssid[20] = "ShivNano";
const char password[20] = "qwertyuiop";
int ledPin = 2; // GPIO 2

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);
    
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    delay(5000);
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
// Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
// Match the request
    int value = LOW;
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH);
      value = HIGH;
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW);
      value = LOW;
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

   client.println("<title>Login</title>");
   client.println("<script language=javascript>");
   client.println("function test()");
   client.println("{");
   client.println("var vl1=frm.text1.value;");
   client.println("var vl2=frm.text2.value;");
   client.println("if( vl1 == 'team' && vl2=='123')");
   client.println("{");
   client.println("var div1= document.getElementById('result')");
   client.println("div1.style.display= 'inline'");
   client.println("var div2=document.getElementById('login')");
   client.println("(div2.style.display= 'none')");
   client.println("}");
   client.println("else");
   client.println("{");
   client.println("alert('wrong credentials');");
   client.println("}");
   client.println("}");
   client.println("</script>");
   client.println("<body>");
   client.println(" <div id=login class=login style='display:inline'>");
   client.println("<form name='frm'>");
   client.println("userid<input type='text1' name='text1' id='text1'>");
   client.println("<br>password<input type='password' name='text2' id='text2'>");
   client.println("<br>");
   client.println("<input type='button' name='button1'value='login' onClick=test()>");
   client.println("</form>");
   client.println("</div>");
   client.println("<div id=result class=result style='display:none'>");
   
   
   client.println("<button>");
   client.print("Led is now:");
    if(value == HIGH) {
    client.print("On");
    } else {
    client.print("Off");
    }
    client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
    client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />");
    client.println("</button>");
    
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");
}
