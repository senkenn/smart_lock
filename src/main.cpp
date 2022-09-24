#include <Arduino.h>
#include <ESP32Servo.h>

#define BTM_PIN   15
#define SERVO_PIN 4

#define LOCK_ANGLE   90 // Degree
#define UNLOCK_ANGLE 0  // Degree

#define WAIT_TIME_TO_LOCK 180 * 1000 // ms

Servo      servo;
void setup() {

  // ピン
  pinMode(BTM_PIN, INPUT);
  servo.attach(SERVO_PIN);

  // モーターの初期位置
  servo.write(LOCK_ANGLE);
}

void loop() {

  // ボタンの状態を取得
  int state = digitalRead(BTM_PIN);

  // ボタン押下なら解錠
  if (state == HIGH) {

    // 解錠
    servo.write(UNLOCK_ANGLE);

    delay(WAIT_TIME_TO_LOCK);

    // 施錠
    servo.write(LOCK_ANGLE);
  }
}
