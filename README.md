# 2026-Team-2-BLE-Smart-Traffic-

BLE Smart Traffic integrates BLE communication between a Raspberry Pi3B-controlled traffic light and an Arduino Rev3-operated small vehicle such that the vehicle does not require computer vision to interpret the traffic state.
 

## Table of Contents

- [Overview](#overview)  

- [Hardware Components](#hardware-components)  

- [Software and Dependencies](#software-and-dependencies)  

- [Usage](#usage)  

- [Results and Demonstration](#results-and-demonstration)  



## Overview
Describe the objective of your project, the problem it solves, and the main features.

This project consists of two main types of devices with microprocessors. A small smart vehicle will receive a BLE signal emitted from our other device, known as the traffic light. If the traffic light is green, the DX-BT27-A central module will send the message decoded "GREEN" to its paired DX-BT27-A peripheral module such that it will tell the cars they can continue driving, with separate signals and logic for the other traffic states. The vehicles remain autonomous, with the entire system composed of 3 mini-cars and 1 traffic light. An HC-SR04 ultrasonic ranger is also attached to each car to ensure no collisions occur between the smart vehicles. The overall objective is to simulate a small traffic system and allow for efficient routing of autonomous vehicles in a way that does not require computer vision. 

## Hardware Components

List all the components used in your project:
### Traffic Light
- Raspberry Pi 3B+
- DX-BT27-A Central Module (denoted with a small gold marker dot on chip)
- DX-BT27-A USB-A to USB-C Adaptor
#### Breadboard
- 3X 470Ω Resistors
- Green LED (ADALP2000 Analog Parts Kit)
- Yellow LED (ADALP2000 Analog Parts Kit)
- Red LED (ADALP2000 Analog Parts Kit)
- Assorted Jumper Wires

### Smart Vehicles
- Arduino Rev3
- 9V Battery for Arduino Rev3
- DX-BT27-A Peripheral Module (denoted without the small gold marker)
- HC-SR04 Ultrasonic Ranger
- 4X AA Batteries for L298N 
- L298N Motor Driver Module
- YIKESHU DIY 2WD Smart Robot Chassis Kit (including body, wheels, and motor)
- Assorted Jumper Wires
#### Smaller Breadboard
- 3X 1kΩ Resistors for DX-BT27-A voltage-divided TX pin power

## Software and Dependencies
### Traffic Light
- Python
#### Libraries
- serial
- time
- RPi.GPIO

### Smart Vehicles
- C++
#### Headers
- SoftwareSerial.h

## Usage
In order to run this system, we used the Arduino IDE to compile the C++ scripts onto the smart cars and used the headless approach via SSH to execute TrafficLight/main.py from an external laptop onto the Raspberry Pi3B+. This can be bypassed via a separate monitor, but this method minimizes hardware and space requirements.

## Results and Demonstration

[![Demonstration Video](https://youtube.com)](https://www.youtube.com/watch?v=APwNRAdVClQ)

As can be seen in the demonstration video, we were able to successfully influence the speed of the wheels on the smart vehicle based on the BLE signal received, and the cars stop when the ultrasonic sensor detects an object in front of them. Multiple cars are able to be run simultaneously if multiple DX-BT27-A central modules are attached to the same Raspberry Pi. This procedure is started in TrafficLight/main.py when the variable ser2 is initiated on line 6 and can be expanded to as many serial ports as your microprocessor contains. In order to simulate a more realistic traffic flow system, the traffic light would need to know the smart cars relative positioning, which would require at least 3 central modules to triangulate from via RSSI readings. This, along with testing the reliability of the cars receiving BLE signals at fast speeds, are the next steps towards innovating in our smart traffic system. 
