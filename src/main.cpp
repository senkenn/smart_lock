#include <Arduino.h>
#include <my-servo.h>
#include <my-wifi.h>

void setup() {

  // シリアル通信
  Serial.begin(9600);

  connectToWiFi();
  webApiConfig();

  servoConfig();
}

void loop() {
}
