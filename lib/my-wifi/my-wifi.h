#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>

const IPAddress localIP(192, 168, 11, 7);
const IPAddress gateway(192, 168, 11, 1);
const IPAddress subnet(255, 255, 255, 0);

void connectToWiFi();
void webApiConfig();
void wait(unsigned int waitTIme);

#endif // MY_WIFI_H
