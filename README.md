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

 

## Hardware Components

List all the components used in your project:
### Traffic Light
Raspberry Pi 3B+
DX-BT27-A Central Module (denoted with a small gold marker dot on chip)
DX-BT27-A USB-A to USB-C Adaptor
#### Breadboard
3X 470Ω Resistors
Green LED (ADALP2000 Analog Parts Kit)
Yellow LED (ADALP2000 Analog Parts Kit)
Red LED (ADALP2000 Analog Parts Kit)
Assorted Jumper Wires

### Smart Vehicles
Arduino Rev3
9V Battery for Arduino Rev3
DX-BT27-A Peripheral Module (denoted without the small gold marker)
HC-SR04 Ultrasonic Ranger
4X AA Batteries for L298N 
L298N Motor Driver Module
YIKESHU DIY 2WD Smart Robot Chassis Kit (including body, wheels, and motor)
Assorted Jumper Wires
#### Smaller Breadboard
3X 1kΩ Resistors for DX-BT27-A voltage-divided TX pin power

## Software and Dependencies
### Traffic Light
Python
#### Libraries
serial
time
RPi.GPIO

### Smart Vehicles
C++
#### Headers
SoftwareSerial.h
