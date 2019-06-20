const int pingPin = D7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = D6; // Echo Pin of Ultrasonic Sensor
int redPin= D1;
int greenPin = D2;
int bluePin = D3;


void setup() {
   Serial.begin(9600); 
   
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
  
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   
   pinMode(D5,OUTPUT);
   digitalWrite(D5,LOW);
}

void loop() {
   
   long duration,inches,cm,dist;
   
   
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   dist = duration*0.034/2;
   delay(1000);
   
   if( dist < 4){
     Serial.println(dist);
     
     analogWrite(redPin,0);
     analogWrite(greenPin,1024);
     analogWrite(bluePin,1024);// Red Color
     digitalWrite(D5,HIGH);   
   }
   if((4< dist) && (dist < 6)){
     Serial.println(dist);
     analogWrite(redPin,0);
     analogWrite(greenPin,512);
     analogWrite(bluePin,1024); // ORANGE
     digitalWrite(D5,HIGH);
     delay(2000);
    
   }
   if((6 < dist) && (dist < 8)){
     Serial.println(dist);
     analogWrite(redPin,0);
     analogWrite(greenPin,0);
     analogWrite(bluePin,1024); // YELLOW
     digitalWrite(D5,HIGH);
     delay(4000);
   }
   if((8 < dist) && (dist < 12)){
    Serial.println(dist);
    analogWrite(redPin,1024);
    analogWrite(greenPin,0);
    analogWrite(bluePin,1024); //GREEN
    digitalWrite(D5,LOW);
   }
   if((12 <dist)&& (dist <16)){
    Serial.println(dist);
    analogWrite(redPin,1024);
    analogWrite(greenPin,1024);
    analogWrite(bluePin,0); //BLUE
    digitalWrite(D5,LOW);   
   }
   if((16<dist) && (dist <20)){
    Serial.println(dist);
    analogWrite(redPin,0);
    analogWrite(greenPin,1024);
    analogWrite(bluePin,0); //INDIGO
    digitalWrite(D5,LOW);
   }
   if((20 < dist) && (dist < 24)){
    Serial.println(dist);
    analogWrite(redPin,592);
    analogWrite(greenPin,1024);
    analogWrite(bluePin,844); //VIOLET
    digitalWrite(D5,LOW);
   }

}
