# WebServer on ESP8266EX

This project demonstrates how to run an **ESP8266EX** microcontroller as a Wi-Fi Access Point with a built-in web server and an SSD1306 OLED display.

## Features
- Creates its own Wi-Fi network (SSID and password can be configured in the code).
- Runs a simple HTTP server on port 80.
- Displays Wi-Fi status and IP address on the OLED display (128x64).
- Serves a webpage accessible via any connected device.

## Tech Stack
- **Microcontroller:** ESP8266EX (4MB Flash, Wi-Fi 802.11 b/g/n)
- **Language:** C++ (Arduino framework)
- **Libraries:**
  - ESP8266WiFi
  - ESP8266WebServer
  - Adafruit GFX
  - Adafruit SSD1306
  - Wire

## Requirements
- Arduino CLI (`arduino-cli`)
- ESP8266 core installed:
  ```bash
  arduino-cli core update-index
  arduino-cli core install esp8266:esp8266
  ```
- SSD1306 OLED display (I²C, address 0x3C)

## Build & Upload
The project uses a `Makefile`
```bash
# Compile
make

# Upload firmware to the board
make upload

# Open serial monitor
make monitor
```

## Usage 
1. 	Power up the ESP8266EX and open the serial monitor.
2. The board will create a Wi-Fi network with the SSID and password defined in the code:
 ```c 
const char* ssid = "Tenyd";
const char* password = "12345678";
 ```
3.	Connect your phone or PC to this network.
4.	Open the IP address shown on the OLED display (default: 192.168.4.1) in your browser.
5.	You’ll see a simple webpage served by the ESP8266.


