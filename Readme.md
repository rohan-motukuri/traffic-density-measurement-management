## Remote IOT based Traffic Monitoring

This is an IOT domain project built using Arduino UNO and ESP 8266 as the main processors. This project is a basic demo prototyping the concept of traffic monitoring from remote coniditons at intersections of traffi clanes.

## Working

**Constituents**: 
1. Arduino UNO
2. ESP8266
3. Ultrasonic sensor
4. Stepper motor
5. Servo motor

**Explaination**: Arduino UNO primarily controlls the action sof all the sensors and actuators. It then then formats the collected data and using Rx and Tx pins communicates with the ESP8266 serialy using SoftwareSerial. This data is then formatted into HTML `<div>` objects with red rectangular styling applied who synamically showcase the relative traffic density across 4 lanes of traffic.

Basic Schematics of the device:
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/0594bb79-5e11-49e5-8388-4f338eb4bccd)
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/49bd00b1-08af-40a2-85bd-5063d72bb595)

Working:
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/8ce6bb3b-b35f-43ec-8d77-341061e1af2f)
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/06f124a6-cee5-4f07-846c-eaf02cc92fc0)
---
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/ebb9d91f-fd99-49fe-ae62-dc586e19d976)
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/2205ef52-266a-45d2-a44c-4ccf62169761)
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/500154a4-b15b-4e19-9c3a-d617cc3e89a0)


Analysis:
![image](https://github.com/rohan-motukuri/traffic-density-measurement-management/assets/123802857/c76c82fc-6218-4fef-99db-9c66fdea6c0e)
