#include <SoftwareSerial.h>
SoftwareSerial EEBlue(10, 11); // RX | TX
String data;
void setup()
{
Serial.begin(9600);
EEBlue.begin(9600); //Default Baud for comm, it may be different for your Module.
Serial.println("The bluetooth Module.");
pinMode(8,OUTPUT);
}

void loop()
{

// Feed any data from bluetooth to Terminal.
if (EEBlue.available())
{
data=EEBlue.readStringUntil('\r');
Serial.println(data);
 if (data=="on"){
  Serial.println("Led On");
   digitalWrite(8,HIGH);}
 else if(data=="off")
    digitalWrite(8,LOW);
    

}

// Feed all data from termial to bluetooth
if (Serial.available())
EEBlue.write(Serial.read());
}
