# Hardware Design and Implementation

● **ESP32 Microcontroller**: This will act as the main controller for handling WiFi and MQTT communication and also will operate the relay module based on messages received from the mobile application.

● **Relay Module**: A single channel relay module will be used to control the target system’s motor with connections to a 3.3V or 5V power supply, a connection leading to ground and the last connection to receive control signals from an ESP32 GPIO pin.

● **Power Supply**: A 5V power supply is required to power the ESP32 and relay module. Consistent and stable power supply is necessary for the system to avoid any fluctuations which might reset the ESP32.

● **QR Code stickers**: Unique QR Code stickers on every target system will be required. Each of these QR Code stickers will contain a unique identifier for every manual target.

● **WiFi Router**: A WiFi router must be set up to provide a stable and secure network for the ESP32 microcontroller and mobile application to communicate.
