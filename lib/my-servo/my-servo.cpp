#include "my-servo.h"

Servo servo;

void servoConfig() {

  // ピン
  pinMode(BTM_PIN, INPUT);
  servo.attach(SERVO_PIN);

  // モーターの初期位置
  servo.write(LOCK_ANGLE);
}

void servoLoop() {

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

/// @brief サーボモーターの状態を返す
/// @param state HTML内のプレースホルダー
String servoState(const String &state) {
  Serial.println("state: " + state);
  return "UNLOCK";
};
