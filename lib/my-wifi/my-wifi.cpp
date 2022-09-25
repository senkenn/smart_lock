#include "my-wifi.h"

WiFiServer server(80);

// WiFiサーバーセットアップ
void connectToWiFi() {

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
}

// WiFiサーバーループ
void wifiServerLoop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  Serial.println("New Client."); // print a message out the serial port

  String currentLine = "";     // make a String to hold incoming data from the client
  while (client.connected()) { // loop while the client's connected
    if (client.available()) {  // if there's bytes to read from the client,
      char c = client.read();  // read a byte, then
      Serial.write(c);         // print it out the serial monitor
      if (c == '\n') {         // if the byte is a newline character

        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {

          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          // the content of the HTTP response follows the header:
          client.print("Hello<br>");

          // The HTTP response ends with another blank line:
          client.println();
          // break out of the while loop:
          break;

        } else { // if you got a newline, then clear currentLine:
          currentLine = "";
        }

      } else if (c != '\r') { // if you got anything else but a carriage return character,
        currentLine += c;     // add it to the end of the currentLine
      }

      // Check to see if the client request was "GET /H" or "GET /L":
      if (currentLine.endsWith("GET /H")) {
        digitalWrite(5, HIGH); // GET /H turns the LED on
      }
      if (currentLine.endsWith("GET /L")) {
        digitalWrite(5, LOW); // GET /L turns the LED off
      }
    }
  }

  // close the connection:
  client.stop();
  Serial.println("Client Disconnected.");
}
