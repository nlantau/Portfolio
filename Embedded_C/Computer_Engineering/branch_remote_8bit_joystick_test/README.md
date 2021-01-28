## Remote - Test UART 8 bit

### Parts included
+ Arduino Uno
+ Joystick

### Functionality - Goals
1. 8-bit ADC for x- and y-axis of joystick
2. **Differential algorithm**
    + Allows for all calculations on remote
3. TX masked unsigned char
    + LSB determines x- or y-axis ie Left or Right motor on robot
```c
adc_x = (adc_x & 0xFE);
adc_y = (adc_y & 0xFE) | (1 << 0);
```

4. Robot RX and conditions mask

```c
if (rx_pwm & (1 << 0))
{
    OCR0A = rx_pwm;
}
else
{
    OCR0B = rx_pwm;
}
```

