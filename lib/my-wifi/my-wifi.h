#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <WiFi.h>

#include "my-ssid-pass.h"

const IPAddress localIP(192, 168, 11, 6);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);

void connectToWiFi();
void wifiServerLoop();

#endif // MY_WIFI_H
