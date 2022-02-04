#!/usr/bin/env python3
# nlantau, 2021-05-19

import serial

PORT = r'/dev/ttyACM0'
BAUD = 9600

with serial.Serial(PORT, BAUD) as ser:
    while True:
        line = ser.readline().decode('utf-8').strip()
        print(f'{line}')

