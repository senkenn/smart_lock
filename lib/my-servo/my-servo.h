#include <ESP32Servo.h>

#define BTM_PIN   15
#define SERVO_PIN 4

#define LOCK_ANGLE   90 // Degree
#define UNLOCK_ANGLE 0  // Degree

#define WAIT_TIME_TO_LOCK 3 * 1000 // ms

/// @brief サーボモーターの状態を返す
/// @param state HTML内のプレースホルダー
auto servoState = [](const String &state) {
  Serial.println("state: " + state);
  return "UNLOCK";
};

void servoConfig();
void servoLoop();
