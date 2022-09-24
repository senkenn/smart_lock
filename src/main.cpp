#include <Arduino.h>
#include <ESP32Servo.h>
#include <SPIFFS.h>
#include <WiFi.h>

#define BTM_PIN   15
#define SERVO_PIN 4

#define LOCK_ANGLE   90 // Degree
#define UNLOCK_ANGLE 0  // Degree

#define WAIT_TIME_TO_LOCK 180 * 1000 // ms

Servo      servo;
WiFiServer server(80);

void setup() {

  // シリアル通信
  Serial.begin(9600);

  // WiFi
  WiFi.begin(); // 一度SSIDとパスワードを書き込めばESP32内部に保存される
  Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    Serial.print(".");
    delay(100);
  }
  Serial.println(" connected!");

  server.begin();

  Serial.print("HTTP Server: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  // ピン
  pinMode(BTM_PIN, INPUT);
  servo.attach(SERVO_PIN);

  // モーターの初期位置
  servo.write(LOCK_ANGLE);
}

void loop() {

  // WiFi
  WiFiClient client = server.available();
  if (client) {
    client.println("Hello World!");
  }

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
