#include <SoftwareSerial.h>

//PINS-MOTOR//
const int left_pos = 10;
const int left_neg = 11;
const int right_pos = 12;
const int right_neg = 13;
const int left_pwm = 5;
const int right_pwm = 6;

//PINS-RANGER//
const int trig = 8;
const int echo = 9;

//PINS-BLE//
const int RX = 2;
const int TX = 4;
SoftwareSerial bleSerial(RX,TX);

//========== Drive Functions ==========//
void drive_forward() {
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);

  delay(500);
  analogWrite(left_pwm,245);
  analogWrite(right_pwm,215);
}
void drive_slow_forward() {
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);

  delay(200);
  analogWrite(left_pwm,123);
  analogWrite(right_pwm,108);
}

void drive_backward() {
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,1);
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,1);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);

  delay(500);
  analogWrite(left_pwm,245);
  analogWrite(right_pwm,235);
}

void drive_stop() {
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,0);
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,0);
}

void drive_left() {
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);

  delay(200);
  analogWrite(left_pwm,135);
  analogWrite(right_pwm,250);
  delay(2200);
  drive_stop();
  delay(500);
}

void drive_right() {
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);

  delay(500);
  analogWrite(left_pwm,250);
  analogWrite(right_pwm,60);
  delay(1800);
  drive_stop();
  delay(500);
}

//========== Ranger Functions ==========//
float getDistance() {
  float duration, distance;
  
  digitalWrite(trig, LOW);  //Clear trigger 
  delay(2);
  digitalWrite(trig, HIGH); 
  delay(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.0343/2; // converts the time between click and echo to a distance in cm
  return distance;
}


//========== Main Functions ==========//
void setup() {
  //Motors
  pinMode(left_pos,OUTPUT);
  pinMode(left_neg,OUTPUT);
  pinMode(right_pos,OUTPUT);
  pinMode(right_neg,OUTPUT);
  pinMode(left_pwm,OUTPUT);
  pinMode(right_pwm,OUTPUT);

  //Ranger
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
  bleSerial.begin(9600);
  Serial.println("System Ready. Waiting for BLE commands...");
}
//The main loop that decides how the car will respond to the BLE signals
void loop() {
  float distance = getDistance();
  if(distance <= 10) {
    drive_stop(); //Regardless of traffic light state, if the ranger detects 
    //an object, the car will stop moving to prevent collision
  }

  else if(bleSerial.available()) {
    String command = bleSerial.readStringUntil('\n'); //Parses serial string
    command.trim(); 

    if(command == "GREEN") {
      drive_forward();
      Serial.println("Moving Forward Quickly");
    }
    else if(command == "YELLOW") {
      drive_slow_forward();
      Serial.println("Moving Forward Slowly");
    }
    else if(command == "RED") {
      drive_stop();
      Serial.println("Stopped");
    }
  }
}
