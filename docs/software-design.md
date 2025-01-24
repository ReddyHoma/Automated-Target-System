# Software Design and Implementation

● **Mobile Application**: A mobile application will be developed with different screens like Dashboard, Profile Screen, Login Screen, Past Bookings Screen and Session Booking Screen to handle all requests from the shooter efficiently. This mobile app will employ Google’s Firebase services, namely Cloud Firestore and Authentication.

● **Backend Services**: Firebase Firestore or Cloud Firestore will act as the database which contains two collections, namely ‘users’ to store shooter credentials and ‘bookings’ to store booking data. Another backend service will be Firebase Authentication which will manage login, registration and manual target authentication upon scanning the QR code sticker.

● **MQTT Communication**: MQTT protocols will be used to send control messages from the mobile application to the ESP32 regarding the status of the target system. This protocol will also facilitate transmission of data from the ESP32 to the app regarding target status and operational errors if any.

● **Frameworks Used**: Flutter will act as the primary SDK while integrating Android Studio and Visual Studio Code services. Arduino IDE will be used for developing code for the ESP32 microcontroller.

● **Programming Languages Used**: Dart acts as the programming language for mobile app development. Arduino uses a variant of the C++ programming language for the ESP32 microcontroller.
