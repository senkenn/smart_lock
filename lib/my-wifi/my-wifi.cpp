#include <my-servo.h>
#include <my-wifi.h>

AsyncWebServer server(80); // ポート設定

/// @fn
/// @brief WiFiサーバーセットアップ
void connectToWiFi() {

  // SPIFFSのセットアップ
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // IPアドレスの固定
  if (!WiFi.config(localIP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

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
  Serial.println(WiFi.localIP());

  // サーバースタート
  server.begin();

  Serial.println("Server start!");
}

/// @fn
/// @brief WebAPI設定関数
void webApiConfig() {

  // rootにアクセスしたらindex.htmlを返す
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/index.html"); });

  // 解錠を行う
  server.on("/unlock", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET unlock");

    unlock();

    wait(WAIT_TIME_TO_LOCK); // callback内ではdelayは使えないので経過時間を計る方式

    init();

    request->send(SPIFFS, "/index.html", String(), false, [](const String &) { return "UNLOCKING"; });
  });
}

/// @fn
/// @brief 一定時間待機する（なぜか3秒以上にするとエラーになる）
/// @param waitTIme 待機時間
void wait(unsigned int waitTIme) {

  unsigned long previousMillis = millis();

  while (true) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= waitTIme) {
      break;
    }
  }
}
