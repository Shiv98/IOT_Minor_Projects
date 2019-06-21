#include <SoftwareSerial.h> // arduino nano Bluetooth
SoftwareSerial EEBlue(11,10); // (10) RX TX
//(11) TX RX
void setup()
{
Serial.begin(9600);
EEBlue.begin(38400); //Baud Rate for command Mode.
Serial.println("Enter AT commands!");
}
void loop()
{
// Feed any data from bluetooth to Terminal.
if (EEBlue.available())
Serial.write(EEBlue.read());
// Feed all data from termial to bluetooth
if (Serial.available())
EEBlue.write(Serial.read());
}
