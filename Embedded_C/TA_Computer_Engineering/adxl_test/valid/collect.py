#!/usr/bin/env python3
# nlantau, 2021-05-18

import serial

PORT = r'/dev/ttyACM0'
BAUD = 9600

first = True

with open(r'data.log', "w") as w:
    with serial.Serial(PORT, BAUD) as ser:
        while (data := ser.readline().decode("utf-8").strip()) != "DONE":
            if first:
                print(" > Logging...")
                first = False
            w.write(data + "\n")
