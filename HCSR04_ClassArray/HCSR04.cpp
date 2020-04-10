/**
 * @file HCSR04.cpp
 *
 * @section description_HCSR04_cpp Description
 * HCSR04 class implementation.
 *
 * @section todo_HCSR04_cpp TODO
 * - None.
 *
 * @section author_HCSR04_cpp Author
 * - Created by John Woolsey on 03-30-2020.
 * - Modified by John Woolsey on 04-03-2020.
 *
 * Copyright (c) 2020 Woolsey Workshop.  All rights reserved.
 */


#include "HCSR04.h"


/**
 * The HCSR04 distance sensor instance constructor.
 *
 * @param name      The name of the sensor.
 * @param trigger   The trigger pin of the sensor.
 * @param echo      The echo pin of the sensor.
 * @param maxRange  The maximum range value of the sensor in centimeters.  The default is 400.0.
 * @param minRange  The minimum range value of the sensor in centimeters.  The default is 2.0.
 *
 * @return  Returns a configured instance of an HCSR04 distance sensor.
 */
HCSR04::HCSR04(const char* name, byte trigger, byte echo, float maxRange, float minRange) {
   strcpy(_name, name);
   _trigger = trigger;
   _echo = echo;
   _maxRange = maxRange;
   _minRange = minRange;
   pinMode(_trigger, OUTPUT);
   pinMode(_echo, INPUT);
}


/**
 * Retrieves the distance measured by the distance sensor.
 *
 * @return  Returns the distance sensor's distance.
 */
float HCSR04::distance() {
   return _distance;
}


/**
 * Retrieves the echo pin of the distance sensor.
 *
 * @return  Returns the distance sensor's echo pin.
 */
byte HCSR04::echo() {
   return _echo;
}


/**
 * Retrieves the minimum range value of the distance sensor.
 *
 * @return  Returns the distance sensor's minimum range value.
 */
float HCSR04::minRange() {
   return _minRange;
}


/**
 * Retrieves the maximum range value of the distance sensor.
 *
 * @return  Returns the distance sensor's maximum range value.
 */
float HCSR04::maxRange() {
   return _maxRange;
}


/**
 * Retrieves the name of the distance sensor.
 *
 * @return  Returns the distance sensor's name.
 */
char* HCSR04::name() {
   return _name;
}


/**
 * Initiates and retrieves a distance sensor reading.
 *
 * @return  Returns the distance read by the distance sensor.
 */
float HCSR04::read() {
   // Initiate trigger pulse
   digitalWrite(_trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(_trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(_trigger, LOW);

   // Read echo pulse, 0 for timeout or no pulse
   float duration = pulseIn(_echo, HIGH);  // in microseconds

   // Calculate distance
   _distance = duration * 0.0343 / 2.0;  // in centimeters

   return _distance;
}


/**
 * Retrieves the trigger pin of the distance sensor.
 *
 * @return  Returns the distance sensor's trigger pin.
 */
byte HCSR04::trigger() {
   return _trigger;
}


/**
 * Determines if the distance measured by the distance sensor is within the valid range.
 *
 * @return  Returns the range validity of the distance sensor's measured distance.
 */
bool HCSR04::valid() {
   return (_distance >= _minRange && _distance <= _maxRange);
}
