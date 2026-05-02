#include <SoftwareSerial.h> //Necessary library for BLE communication
//This script is focused purely on testing if the DX-BT27-A periperal module 
//can respond to the central module and drive the motors appropriately. 

// SoftwareSerial(RX, TX)
SoftwareSerial bleSerial(2, 4); 

// Motor Driver Pins
const int ENA = 5;  // PWM 
const int IN1 = 10; //Control left wheel forward
const int IN2 = 11; //Control left wheel backward
const int IN3 = 12; //Control right wheel forward
const int IN4 = 13; //Control right wheel backward

void setup() {
  Serial.begin(9600);    // For PC Debugging
  bleSerial.begin(9600); // For Bluetooth
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.println("System Ready. Waiting for BLE commands...");
}

void loop() {
  if (bleSerial.available()) { //loop will be instructionless until Serial channel is available
    String command = bleSerial.readStringUntil('\n'); //Parsing serial command string
    command.trim();

    if (command == "GREEN") {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 200); // Speed 0-255
      Serial.println("Moving Forward Quickly");
    }
    if (command == "YELLOW") {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 100); // Speed 0-255
      Serial.println("Moving Forward Slowly");
    }  
    else if (command == "RED") {
      analogWrite(ENA, 0);
      Serial.println("Stopped");
    }
  }
}
