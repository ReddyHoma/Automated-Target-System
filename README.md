# Automated-Target-System

## Overview
The **Automated Target System** is an IoT-based solution that integrates a **Flutter** mobile application, **Firebase**, and **ESP32** microcontroller to manage manual target systems. This project allows users to book training sessions, authenticate using QR codes, and control the targets via MQTT communication. The app enables competitive shooting ranges to efficiently manage and monitor target operations in real-time, ensuring secure access and functionality.

## Features
- **User Authentication**: Secure login using Firebase Authentication (email/password).
- **Session Booking**: Users can book a training session for a specific date and time.
- **QR Code Authentication**: QR code scanning for on-site authentication.
- **Real-time Control**: Use MQTT to control targets via the ESP32 microcontroller.
- **Firebase Integration**: Store and fetch user bookings, session details, and other data.
- **Push Notifications**: Notify users about their booking status.
- **Future and Past Bookings Display**: View upcoming and past bookings directly in the app.

## Technologies Used
- **Frontend**: Flutter for mobile app development (iOS/Android).
- **Backend**: Firebase Firestore for database management and Firebase Authentication.
- **Communication**: MQTT for real-time communication between the app and the ESP32 microcontroller.
- **ESP32**: Used for controlling the target relay based on user authentication and booking details.
- **QR Code Scanning**: For on-site user authentication using QR codes.

## Architecture
1. **User Interface (UI)**:
   - The Flutter mobile app is designed with a clean and intuitive UI, allowing users to book training sessions, scan QR codes, and view upcoming/past bookings.
   
2. **Backend**:
   - Firebase serves as the backend to manage user data, bookings, and notifications. Firestore is used to store session details and user-specific information.
   
3. **MQTT Communication**:
   - MQTT is utilized for seamless communication between the mobile app and the ESP32 microcontroller to control pulleys in real-time. The ESP32 listens for MQTT messages and activates the pulley relay accordingly.

4. **QR Code Authentication**:
   - A unique QR code is generated for each pulley. The app scans the code to verify if the user has a valid booking for that specific pulley at the designated time.

## Getting Started

### Prerequisites

1. **Flutter SDK**:
   - Install the Flutter SDK by following the official guide: [Flutter installation](https://flutter.dev/docs/get-started/install).
   
2. **Firebase**:
   - Set up Firebase for your app by creating a Firebase project in the Firebase console and enabling Firestore and Authentication. Follow the guide here: [Firebase setup for Flutter](https://firebase.flutter.dev/docs/overview).

3. **ESP32 Setup**:
   - You need to have an **ESP32** board connected to a relay module to control the pulley. Set up the ESP32 with the Arduino IDE, and ensure you have MQTT communication set up.

4. **MQTT Broker**:
   - You can use public brokers like **test.mosquitto.org** for testing purposes, or set up your own MQTT broker. 

### Installing the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/automated-target-system.git
   cd automated-target-system

