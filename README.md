# Motor RPM Measuring System

This project is a microcontroller-based system designed to measure the real-time RPM (Revolutions Per Minute) of a DC motor. It uses an infrar Hall effect sensor to detect motor rotation and displays the RPM on an LCD screen. This system can be used for educational, industrial, or hobbyist applications where motor speed monitoring is essential.

---

## Features

- Real-time RPM measurement using encoder feedback
- Speed control through a potentiometer
- RPM displayed on 16x2 LCD with I2C module
- Built with Arduino UNO
- Motor control via L298 motor driver
- Modular and educational hardware setup

---

## Components Used

| Component            | Description                         |
|---------------------|-------------------------------------|
| Arduino UNO          | Microcontroller board               |
| DC Motor             | Controlled via motor driver         |
| H2010 Rotary Encoder | Measures shaft rotation pulses      |
| Potentiometer        | Analog input to control speed       |
| L298N Motor Driver   | Dual H-Bridge motor controller      |
| 16x2 LCD with I2C    | Displays RPM                        |
| Power Supply         | 5V-12V (as required by motor)       |
| Breadboard & Wires   | For prototyping                     |

---

## Working Principle

1. The potentiometer sets the motor speed by adjusting PWM output to the L298 driver.
2. The encoder generates pulses as the motor shaft rotates.
3. Arduino counts these pulses over a time interval to calculate RPM.
4. The LCD displays the measured RPM in real-time.

---

## 📁Project Structure
Motor-RPM-Measuring-System/
├── RPM_Measurement.ino # Arduino code file
├── README.md # This file
├── LICENSE # MIT license
