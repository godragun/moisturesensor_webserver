# moisturesensor_webserver

This project utilizes an ESP32 to monitor soil moisture levels using a digital moisture sensor and provides a simple web interface to display the current status (WET/DRY).

# Features ✨
Web Interface: Access the soil moisture status from any device connected to the ESP32's Wi-Fi Access Point.

Real-time Updates: The web page automatically updates the moisture status every second.

Simple Status: Displays "WET (below threshold)" or "DRY (above threshold)" based on the digital sensor output.

Easy Setup: Configurable Wi-Fi credentials directly in the Arduino sketch.

# Hardware Requirements 🛠️
ESP32 Development Board: Any ESP32 board should work (e.g., ESP32-DevKitC, NodeMCU-32S).

Digital Soil Moisture Sensor: A module with a digital output (e.g., FC-28 or similar, ensuring it has a DO pin).

Jumper Wires: For connecting the sensor to the ESP32.

# Wiring Instructions 🔌
Connect your digital soil moisture sensor to the ESP32 as follows:

Sensor VCC 
rightarrow ESP32 3.3V

Sensor GND 
rightarrow ESP32 GND

Sensor DO (Digital Out) 
rightarrow ESP32 GPIO 21 (as defined by DIGITAL_PIN in the code)

# Software Requirements 💻
Arduino IDE: Or PlatformIO, for compiling and uploading the sketch.

ESP32 Boards Manager: Installed in your Arduino IDE.

WiFi.h Library: Standard ESP32 Wi-Fi library.

WebServer.h Library: For creating the web server. This is typically included with the ESP32 board package.

