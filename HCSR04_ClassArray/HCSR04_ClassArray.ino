/**
 * @file HCSR04_ClassArray.ino
 *
 * @mainpage Ultrasonic Distance Sensors Project
 *
 * @section description Description
 * Reads an array of HC-SR04, or compatible, ultrasonic distance sensors.
 *
 * @section circuit Circuit
 * - Four HC-SR04, or compatible, ultrasonic distance sensors (trigger and echo)
 *   connected to pins D2-9 (i.e. S0 trigger = D2, S0 echo = D3;
 *   S1 trigger = D4, S1 echo = D5; ...).
 *
 * @section notes Notes
 * - Use the Serial Monitor to view output while in DEBUG mode.
 * - Source file comments are Doxygen compatible.
 *
 * @section todo TODO
 * - None.
 *
 * @section author Author
 * - Created by John Woolsey on 03-30-2020.
 * - Modified by John Woolsey on 04-09-2020.
 *
 * Copyright (c) 2020 Woolsey Workshop.  All rights reserved.
 */


// Includes
#include "HCSR04.h"


// Defines
#define DEBUG 1        ///< The mode of operation; 0 = normal, 1 = debug.
#define SAMPLE_RATE 1  ///< The sensor sampling rate in Hz.


// Global Instances
/** An array of all connected distance sensors. */
HCSR04 distSensors[] = {
   HCSR04("A", 2, 3, 400, 2),   // full rated range of 2-400 cm for standard HC-SR04 sensor
   HCSR04("B", 4, 5, 450),      // full rated range of 2-450 cm for compatible RCWL-1601 sensor, using default minimum of 2
   HCSR04("C", 6, 7, 250, 10),  // recommended range of 10-250 cm for best accuracy
   HCSR04("D", 8, 9)            // using default range of 2-400 cm
};


/**
 * The standard Arduino setup function used for setup and configuration tasks.
 */
void setup() {
   if (DEBUG) configureSerialBus();  // Serial Monitor
   configureDistanceSensors();
}


/**
 * The standard Arduino loop function used for repeating tasks.
 */
void loop() {
   // Read sensors at the specified sampling rate
   static unsigned long previousTime = millis();
   unsigned long currentTime = millis();
   if (currentTime - previousTime >= 1000/SAMPLE_RATE) {
      readDistanceSensors();
      previousTime = millis();
   }
}


/**
 * Configures all distance sensors.
 */
void configureDistanceSensors() {
   delay(100);  // wait for distance sensors to initialize
   if (DEBUG) {
      Serial.println("Distance sensors configured:");
      for (HCSR04 sensor : distSensors) {
         Serial.print("HCSR04: name = "); Serial.print(sensor.name());
         Serial.print(", trigger = "); Serial.print(sensor.trigger());
         Serial.print(", echo = "); Serial.print(sensor.echo());
         Serial.print(", range = ["); Serial.print(sensor.minRange());
         Serial.print(", "); Serial.print(sensor.maxRange());
         Serial.print("], distance = "); Serial.println(sensor.distance());
      }
      Serial.println();
   }
}


/**
 * Configures serial bus communication.
 */
void configureSerialBus() {
   Serial.begin(9600);  // initialize serial bus
   while (!Serial);     // wait for serial connection
}


/**
 * Reads all distance sensors.
 */
void readDistanceSensors() {
   byte sensorNum = sizeof(distSensors) / sizeof(distSensors[0]);  // number of distance sensors
   for (byte i = 0; i < sensorNum; i++) {
      unsigned long startTime;
      if (DEBUG) { startTime = millis(); }
      distSensors[i].read();
      if (DEBUG) {
         unsigned long stopTime = millis();
         unsigned long measTime = stopTime - startTime;
         Serial.print("Distance sensor "); Serial.print(distSensors[i].name());
         Serial.print(" took "); Serial.print(measTime);
         Serial.print(" ms to read "); Serial.print(distSensors[i].distance());
         Serial.print(" cm");
         Serial.println(distSensors[i].valid() ? "." : " (out of range).");
      }
   }
}
