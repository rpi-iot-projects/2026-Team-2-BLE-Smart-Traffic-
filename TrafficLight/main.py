import serial
import time
import RPi.GPIO as GPIO

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1) #Storing serial port addresses to direct BLE communication
ser2 = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)

GPIO.setmode(GPIO.BOARD) #Each traffic state is powered by a different GPIO pin on the Raspberry Pi
RED_PIN = 11
YELLOW_PIN = 13
GREEN_PIN = 15

GPIO.setup([RED_PIN, YELLOW_PIN, GREEN_PIN], GPIO.OUT, initial=GPIO.LOW)

def control_light(red, yellow, green): #This function decides which pin(s) will be powered
        GPIO.output(RED_PIN, red)
        GPIO.output(YELLOW_PIN, yellow)
        GPIO.output(GREEN_PIN, green)
def debug_light(): #This function adds terminal display confirming traffic logic is as expected
        r = "ON" if GPIO.input(RED_PIN) else "OFF"
        y = "ON" if GPIO.input(YELLOW_PIN) else "OFF"
        g = "ON" if GPIO.input(GREEN_PIN) else "OFF"
        print(f"--- Hardware Status | Red: {r} | Yellow: {y} | Green: {g} ---")

#This is the current logic that controls which state the traffic light (and transitively the cars) is in
try: #Version 1.2:  simple state change via time and no other inputs, but now with multiple DX-BT27-A support
    while True:
        ser.write(b"GREEN\n")
        ser2.write(b"GREEN\n")
        control_light(GPIO.LOW, GPIO.LOW, GPIO.HIGH)
        print("Sent command: GREEN")
        debug_light()

        time.sleep(5)
        ser.write(b"YELLOW\n")
        ser2.write(b"YELLOW\n")
        control_light(GPIO.LOW, GPIO.HIGH, GPIO.LOW)
        print("Sent command: YELLOW")
        debug_light()
        time.sleep(3) #In the future, this may be replaced by 

        ser.write(b"RED\n") #conditionals related to Ultrasonic Ranger data
        ser2.write(b"RED\n")
        control_light(GPIO.HIGH, GPIO.LOW, GPIO.LOW)
        print("Sent command: RED")
        debug_light()
        time.sleep(7)

        counter += 1
        if counter % 10 == 0: #Just a little easter egg to test that multiple pins can be HIGH at once
            control_light(GPIO.HIGH, GPIO.HIGH, GPIO.HIGH)
            debug_light()
            time.sleep(5)
            
except KeyboardInterrupt:
    print("Entering sleep mode")
finally:
    control_light(GPIO.LOW, GPIO.LOW, GPIO.LOW) #Resets the GPIO pins to low so the circuit is off after program termination
    GPIO.cleanup()
    ser.close()
