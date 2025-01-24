# Proposed Work

The project aims to develop a comprehensive solution for managing target systems using a **Flutter** mobile app, **Firebase**, and **ESP32** microcontroller. The approach involves:

● **User Authentication and Login**: The shooter opens the app and either creates a new account or logs in with their credentials if they already have an account. Mobile app authenticates the shooter through Firebase Authentication. On successful authentication, the shooter is directed to the dashboard. If authentication fails, an error message is displayed accordingly.

● **Dashboard Screen**: If the shooter has already booked a few sessions for the future, the dashboard displays details of upcoming bookings by fetching them from Firebase storage. Else, it displays a message conveying no upcoming bookings.

● **QR code authentication**: Upon reaching the range, the shooter has to scan a QR code, through the app, present on the target system which will once again use Firebase Authentication to verify credentials and booking details. If successful, the application displays a message accordingly and sends a message to the ESP32 which then controls a relay to operate the target’s ON/OFF capability. If authentication fails, an error message is displayed accordingly.

● **Booking a session**: The shooter can navigate to the session booking screen from the dashboard which will present input fields required to book a session. The shooter will have to choose the date, preferred time and lane and then click on the book button. The application checks for availability of that lane from its backend. If the lane is available, the app displays a success message accordingly. Else, if the lane is already booked, the app will display a message conveying unavailability and requests the shooter to book for another time or target system.

● **Profile Management**: The shooter will also be able to manage their profile details by navigating to the profile screen from the dashboard. This screen will retrieve data from the Firebase storage and display credentials which were used to create an account. The shooter will be able to edit their details, as and when necessary.

● **Previous Bookings**: Lastly, the shooter will also be able to view details of their past bookings by navigating to the previous bookings screen from the dashboard. This screen will again retrieve the details of past bookings compared to current time and fetch data from the Firebase storage.

● **Real Time Communication with ESP32 Microcontroller**: The application establishes a connection with the MQTT broker as well as the ESP32 Microcontroller present inside each manual target thereby handling requests efficiently.
