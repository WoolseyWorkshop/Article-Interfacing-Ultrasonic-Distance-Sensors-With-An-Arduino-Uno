/**
 * @file HCSR04_Simple.ino
 *
 * @mainpage Ultrasonic Distance Sensor Project
 *
 * @section description Description
 * Reads an HC-SR04, or compatible, ultrasonic distance sensor.
 *
 * @section circuit Circuit
 * - An HC-SR04, or compatible, ultrasonic distance sensor (trigger = D2,
 *   echo = D3).
 *
 * @section notes Notes
 * - Use the Serial Monitor to view output while in DEBUG mode.
 * - Distance sensor measurement times are typically below 50 ms, but can take
 *   up to a second when sensors are disconnected or not functioning properly.
 * - The recommended minimum distance sensor measurement cycle time is 60 ms.
 * - Source file comments are Doxygen compatible.
 *
 * @section todo TODO
 * - None.
 *
 * @section author Author
 * - Created by John Woolsey on 03-24-2020.
 * - Modified by John Woolsey on 04-09-2020.
 *
 * Copyright (c) 2020 Woolsey Workshop.  All rights reserved.
 */


// Defines
#define DEBUG 1  ///< The mode of operation; 0 = normal, 1 = debug.


// Pin Mapping
const byte DistTrigger = 2;  ///< The trigger pin of the distance sensor.
const byte DistEcho = 3;     ///< The echo pin of the distance sensor.


/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
   // Initialize serial bus (Serial Monitor)
   if (DEBUG) {
      Serial.begin(9600);
      while (!Serial);  // wait for serial connection
   }

   // Configure distance sensor
   pinMode(DistTrigger, OUTPUT);
   pinMode(DistEcho, INPUT);
   delay(100);  // wait for distance sensor to initialize
}


/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
   // Read distance sensor
   float distance = readDistanceSensor();
   if (DEBUG) {
      Serial.print("Distance sensor read "); Serial.print(distance);
      Serial.println(" cm.");
   }
   delay(1000);  // wait a second between readings
}


 /**
 * Initiates and retrieves a distance sensor reading.
 *
 * @return  Returns the distance read by the distance sensor.
 */
float readDistanceSensor() {
   // Initiate trigger pulse
   digitalWrite(DistTrigger, LOW);
   delayMicroseconds(2);
   digitalWrite(DistTrigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(DistTrigger, LOW);

   // Read echo pulse, 0 for timeout or no pulse
   float duration = pulseIn(DistEcho, HIGH);  // in microseconds

   // Calculate distance
   float distance = duration * 0.0343 / 2.0;  // in centimeters

   return distance;
}
