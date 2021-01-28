## Robot - Test UART send from Arduino Uno

### Parts included
+ Arduino Uno
+ Potentiometer on A0

### Functionality
1. uart sends a string containing ADC value
2. char rx = UDRO
3. if rx is '1'
    + Turn off RXENO
    + Toggle LED
    + Turn on RXENO

In other words, the robot can continiously send char buffer which is received continiously by the remote.

### Changes needed
The functionality of the code in this branch is the functionality that might be interesting to have on the remote since
the remote should continiously transmit data to PWM motors on the robot and the robot should occationally be able to
transmit (if collision or close to a wall)
