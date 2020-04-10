/**
 * @file HCSR04.h
 *
 * @section description_HCSR04_h Description
 * HCSR04 class.
 *
 * Interfaces with HC-SR04, or compatible, ultrasonic distance sensors.
 *
 * @section notes_HCSR04_h Notes
 * - Distance sensor measurement times are typically below 50 ms, but can take
 *   up to a second when sensors are disconnected or not functioning properly.
 * - The recommended minimum distance sensor measurement cycle time is 60 ms.
 * - Source file comments are Doxygen compatible.
 *
 * @section todo_HCSR04_h TODO
 * - None.
 *
 * @section author_HCSR04_h Author
 * - Created by John Woolsey on 03-30-2020.
 * - Modified by John Woolsey on 04-09-2020.
 *
 * Copyright (c) 2020 Woolsey Workshop.  All rights reserved.
 */


#ifndef HCSR04_H
#define HCSR04_H

#include "Arduino.h"

/**
 * HCSR04 class.
 *
 * Interfaces with HC-SR04, or compatible, ultrasonic distance sensors.
 */
class HCSR04 {
   char _name[21];   ///< The name of the sensor (20 characters max).
   float _distance;  ///< The distance read by the sensor in centimeters.
   byte _trigger;    ///< The trigger pin of the sensor.
   byte _echo;       ///< The echo pin of the sensor.
   float _maxRange;  ///< The maximum range value of the sensor in centimeters.
   float _minRange;  ///< The minimum range value of the sensor in centimeters.
public:
   HCSR04(const char* name, byte trigger, byte echo, float maxRange = 400.0, float minRange = 2.0);  ///< The HCSR04 distance sensor instance constructor.
   float distance();  ///< Retrieves the distance measured by the distance sensor.
   byte echo();       ///< Retrieves the echo pin of the distance sensor.
   float minRange();  ///< Retrieves the minimum range value of the distance sensor.
   float maxRange();  ///< Retrieves the maximum range value of the distance sensor.
   char* name();      ///< Retrieves the name of the distance sensor.
   float read();      ///< Initiates a distance sensor reading.
   byte trigger();    ///< Retrieves the trigger pin of the distance sensor.
   bool valid();      ///< Determines if the distance measured by the distance sensor is within the valid range.
};

#endif  // HCSR04_H
