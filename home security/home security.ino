#include <SoftwareSerial.h>
#define trigPin 8
#define echoPin 9

SoftwareSerial mySerial(3, 2);

int redled = 13;

void setup()
{
  mySerial.begin(9600);      
  Serial.begin(9600);   
  SoftwareSerial mySerial(3, 2);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  mySerial.begin(9600); 
  Serial.println("logging time completed!");

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

  
  if (distance_in_cm <= 10) {
    digitalWrite(redled,HIGH);
    Serial.println("Motion detected!");
    Serial.println("calling....");
     
   
    mySerial.println("AT"); 
    updateSerial();
  
    mySerial.println("AT+CMGF=1"); 
    updateSerial();
    
    mySerial.println("AT+CMGS=\"+916205575120\"");
    updateSerial();
    
    mySerial.print("Security Alert"); 
    updateSerial();
    
    mySerial.write(26);
    
    mySerial.println("ATD+ +916207142991;");
    updateSerial();
    
    delay(30000); 
    
    mySerial.println("ATH"); 
    updateSerial();

   delay(2000);
  }
}
  void updateSerial(){ // This is an important function for GSM to work. DO NOT DELETE !!!!!!!!!
    delay(500);
    
    while (Serial.available()) 
    { 
     mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
    }

    while(mySerial.available()) 
    {
     Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
    }
    
  }