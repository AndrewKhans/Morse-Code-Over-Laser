# Morse-Code-Over-Laser

An arduino project

## Project Overview

  This project consists of an emitter and receiver circuit, both of which are powered by their own Arduino boards. The emitter’s Arduino program takes a string message and encodes it into Morse code, which is then pulsed by the laser diode. The laser is pointed at the photoresistor on the receiver circuit, which has its voltage monitored by the receiver circuit. Since an Arduino board cannot monitor resistance directly, we used a voltage divider circuit, with the photocell as R1, and a 10k resistor as R2. By reading the voltage over the photocell, we get an analog reading that changes based on the amount of light shining on the photoresistor. The program on the receiver’s Arduino board turns the length of the laser pulses into Morse code, translates it to English characters, and then prints it to the serial monitor of the computer so it may be read by the user.

```
Threshold = 850
```
This value should be configured based off the light level of your room.

## Building The Project

### Parts List

### Circuit Diagrams

### Uploading Code


## Authors

* **Andrew Khanschassoff** - *Crippled* - [Email](mailto:khansa@rpi.edu)

* **Alan Bahr** - *Coding + Moral Support* - [Email](mailto:bahra@rpi.edu)

## Acknowledgments

* Jeff - Great High-Fives
