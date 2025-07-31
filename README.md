# Pocket Weather Station
OBS: NOT DONE - IMAGES AND CAD FILES WILL BE ADDED TO FINISHED THING. (+ APPROPRIATE BATTERY)

This is a simple portable, pocket-size weather station. The idea of this isnt for it to be very advanced or have loads of sensors but rather to make a small version that still does the job. Future version might have more sensors and use the ESPs connectivity options more. Use either Arduino IDE or PlatformIO to set this up.

## Hardware Setup
**Components**
| Component |
| --- |
| ESP32-C3 Supermini |
| 128x32 OLED SSD1306 I2C | 
| AHT10 Temperature and humidity sensor |
| TTP223 Touch Sensor | 

**128x32 OLED**
| OLED Pin | ESP32-C3 GPIO |
| --- | --- |
| SCK | GPIO9 |
| SDA | GPIO8 |
| VIN | 3V3 |
| GND | GND |

**AHT10 Temperature and Humidity Sensor**
| AHT10 Pin | ESP32-C3 GPIO |
| --- | --- |
| SCK | GPIO9 |
| SDA | GPIO8 |
| VIN | 3V3 |
| GND | GND |

**TTP223 Touch Sensor**
| AHT10 Pin | ESP32-C3 GPIO |
| --- | --- |
| VCC | 3V3|
| GND | GND |
| I/O | GPIO2 |

