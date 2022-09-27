#include "my-wifi.hpp"

AsyncWebServer server(80); // ポート設定

// WiFiサーバーセットアップ
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

/// WebAPI設定関数
/// @param callback 指定されたパスへのレスポンス時に実行されるコールバック関数
void webApiConfig(std::function<String(String)> callback) {

  // GETリクエストに対するハンドラーを登録
  // rootにアクセスされた時のレスポンス
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/index.html"); });

  // style.cssにアクセスされた時のレスポンス
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) { request->send(SPIFFS, "/style.css", "text/css"); });

  server.on("/unlock", HTTP_GET, [callback](AsyncWebServerRequest *request) {
    Serial.println("GET unlock");
    request->send(SPIFFS, "/index.html", String(), false, callback); // HTML内のプレースホルダーの数だけcallback関数が呼ばれる
  });

  server.on("/lock", HTTP_GET, [callback](AsyncWebServerRequest *request) {
    Serial.println("GET lock");
    request->send(SPIFFS, "/index.html", String(), false, callback);
  });
}
