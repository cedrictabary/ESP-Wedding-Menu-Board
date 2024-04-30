# ESP-Wedding-Menu-Board

I designed a menu board for my wedding based on an ESP8266 D1 Mini board.

HD44780 20x04 LCD screen with I2C converter for the menu display.

7-segment display controlled by a TM1637 for the table number.

# Pinning

Pin D7 is used as PWM output to control LCD brightness with a NPN/PNP switch to provide power directly from VCC.

Pin D5 D6 are used as CLK/DIO to control the TM1637 chip.

Pin D1 D2 are used as SDA/SCL to control the LCD display.

# Schematics

![menu-lcd](https://github.com/cedrictabary/ESP-Wedding-Menu-Board/assets/2911212/38eb01e9-d210-4f87-bdb3-a27d515225f5)

# The menu board

![Menu board](https://github.com/cedrictabary/ESP-Wedding-Menu-Board/assets/2911212/c5f92784-00e0-45e0-b526-02beaf88fc56)

# Special thanks

To JiLPi & Auré who hacked my board during my wedding dinner and published their code: [ArduinoWedding](https://github.com/beaujean/ArduinoWedding)
