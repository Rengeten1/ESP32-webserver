# ESP32 WROOM - Web Server with LED Control

## Overview
A simple web server running on ESP32 WROOM microcontroller that allows you to control the built-in LED and monitor device status via a web browser.

**Author:** Rownak Deb Kabya   
**Platform:** PlatformIO

---

## Features
- WiFi connectivity  
- Web-based control panel  
- Toggle built-in LED (GPIO 2) remotely  
- Real-time ESP32 status monitoring  
- Serial debug output  
- Responsive HTML interface  

---

## Hardware Requirements
- **ESP32 WROOM** microcontroller
- **USB cable** (data + power)
- **WiFi network** (2.4GHz)

---

## Wiring
There were no external wiring used as the built-in led was used.

---

## Installation

### Prerequisites
- PlatformIO CLI or VS Code extension installed
- ESP32 board support (`espressif32`)

### Clone
```bash
git clone https://github.com/Rengeten1/esp32-webserver.git
```

Open VScode and click open project.

Choose the cloned directory.

Change the password and SSID.

Then build, upload and done!