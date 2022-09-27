#include <Arduino.h>
#include <my-servo.hpp>
#include <my-wifi.hpp>

void setup() {

  // シリアル通信
  Serial.begin(9600);

  connectToWiFi();
  webApiConfig(servoState);

  servoConfig();
}

void loop() {
  servoLoop();
}
