#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
#define trigPin 8
#define echoPin 9
int redled = 13;


void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
 mySerial.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println(" logging time completed!");
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(redled, OUTPUT);
digitalWrite(redled, LOW);
delay(100);

}

void loop() {

  long time_duration, distance_in_cm;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time_duration = pulseIn(echoPin, HIGH);
  distance_in_cm = time_duration / 29 / 2;
  

  Serial.print(distance_in_cm);
  Serial.println(" cm");
  delay(1000);

  //Ranging Distance − 2cm – 400 cm
  //if the distance is equal or more then 70 cm
  
  if (distance_in_cm <= 20) {
    digitalWrite(redled,HIGH);
    Serial.println("Motion detected!");
    Serial.println("sending message....");
     
     mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
   
  
   delay(2000);
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+916205575120\"");
    updateSerial();
    mySerial.print("Security Alert"); 
    updateSerial();
    mySerial.write(26);
 updateSerial();
      mySerial.println("ATD+ +916205575120"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    updateSerial();
    delay(30000); // wait for 30 seconds...
    mySerial.println("ATH"); //hang up
  updateSerial();                       

  }
 else{
  digitalWrite(redled,LOW);
}
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
}
}