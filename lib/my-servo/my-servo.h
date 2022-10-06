#ifndef MY_SERVO_H
#define MY_SERVO_H

#include <ESP32Servo.h>

#define SERVO_PIN 4

#define INIT_ANGLE   0  // Degree
#define UNLOCK_ANGLE 30 // Degree

#define WAIT_TIME_TO_LOCK 3 * 1000 // ms

void   servoConfig();
void   init();
void   unlock();

#endif // MY_SERVO_H
