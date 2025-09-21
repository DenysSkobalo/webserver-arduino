#include "webserver.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid     = "SSID";
const char* password = "Password";

ESP8266WebServer server(80);

String message = "Hello ESP8266!";

void handleRoot() {
  String html = "<html><body>"
                "<h2>ESP8266 OLED WebServer</h2>"
                "<form action='/set' method='GET'>"
                "Text: <input type='text' name='msg'>"
                "<input type='submit' value='Send'>"
                "</form>"
                "<p>Current: " + message + "</p>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void handleSet() {
  if (server.hasArg("msg")) {
    message = server.arg("msg");

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println(message);
    display.display();
  }
  handleRoot();
}

void ws_setup() {
  Serial.begin(115200);

  Wire.begin(12, 14);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 not found");
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  String ip = WiFi.localIP().toString();
  Serial.println("WiFi connected: " + ip);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("WiFi OK");
  display.println("IP:");
  display.println(ip);
  display.display();

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void ws_loop() {
  server.handleClient();
}

