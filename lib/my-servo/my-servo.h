#ifndef MY_SERVO_H
#define MY_SERVO_H

#include <ESP32Servo.h>

#define BTM_PIN   15
#define SERVO_PIN 4

#define LOCK_ANGLE   90 // Degree
#define UNLOCK_ANGLE 0  // Degree

#define WAIT_TIME_TO_LOCK 3 * 1000 // ms

void   servoConfig();
void   servoLoop();
String servoState(const String &);

#endif // MY_SERVO_H
