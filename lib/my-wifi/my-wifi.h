#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

const IPAddress localIP(192, 168, 11, 6);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);

void connectToWiFi();
void webApiConfig(std::function<String(String)>);

#endif // MY_WIFI_H
