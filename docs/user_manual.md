# User Manual

## Setup Instructions
1. Connect the potentiometer to the ADC input of the LPC2148.
2. Connect the LCD display to the GPIO pins of the LPC2148.
3. Wire the motor to a transistor or relay controlled by a GPIO pin.
4. Connect the LED to a GPIO pin for alerts.

## Operating the System
- When the soil moisture level is below the threshold, the motor will turn on and an alert LED will blink.
- When the moisture level is adequate, the motor will turn off and the LED will remain off.
