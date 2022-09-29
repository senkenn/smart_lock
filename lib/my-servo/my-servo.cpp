#include "my-servo.h"

Servo servo;

/// @brief 施錠
void lock() {
  servo.write(LOCK_ANGLE);
}

/// @brief 解錠
void unlock() {
  servo.write(UNLOCK_ANGLE);
}

/// @brief サーボモーター設定
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
    unlock();

    delay(WAIT_TIME_TO_LOCK);

    // 施錠
    lock();
  }
}

/// @brief サーボモーターの状態を返す
/// @param state HTML内のプレースホルダー
String servoState(const String &state) {

  const int angle = servo.read();
  Serial.println(angle);

  if (angle == LOCK_ANGLE) { // もしロック状態ならば
    return "LOCK";
  } else {
    return "UNLOCKING";
  }
};
