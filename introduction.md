# Introduction

## Background
Shooting Ranges often face challenges in efficiently managing and scheduling use of their target systems due to a large number of shooters training every single day. Traditionally, rarely any shooting ranges even have a lane booking system leading to shooters unable to get any training time in the range. The few ranges which do have a lane booking system, often do it manually which can be prone to errors, lacking in real-time visibility. Integrating technology into this manual process of lane booking systems would allow significant increase in efficiency and also enhance user experience.

## Purpose
By providing athletes with a mobile application to book their training sessions, it would allow them to keep track of their previous training sessions and check real time availability of lanes for training, leading to improved convenience as well as a clear state of mind while stepping into the range. Integrating with IoT devices like an ESP32 microcontroller allows for real time monitoring and access to the targets, ensuring timely and accurate responses to any requests or errors. Having an automated system would also decrease the administrative overhead, decreasing errors and optimal target utilisation at the shooting range. In larger ranges with more than 50 lanes or so, it would also offer scalability to effectively handle the demand and monitor every single target and its condition referring to user requests. By making use of a suitable backend server, this automated system would provide administration with the ability to analyse usage patterns and make informed decisions in the management of the facility as a whole.

## Scope
This system will enable:
- **Real-time booking** of training sessions.
- **User authentication** via QR codes.
- **Control and operation** of the target system through MQTT and ESP32.
- **Real-time data updates** via Firebase Firestore.
