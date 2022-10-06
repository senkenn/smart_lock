#include <my-servo.h>

Servo servo;

/// @brief 初期状態にする
void init() {
  servo.write(INIT_ANGLE);
}

/// @brief 解錠
void unlock() {
  servo.write(UNLOCK_ANGLE);
}

/// @brief サーボモーター設定
void servoConfig() {

  // ピン
  servo.attach(SERVO_PIN);

  // モーターの初期位置
  servo.write(INIT_ANGLE);
}
