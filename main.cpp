#include "main.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char *ssid = "Tenyd";
const char *password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from Tenyd</h1>");
}

void ws_setup() {
  Serial.begin(115200);
  Wire.begin(12, 14);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 not found");
    for (;;)
      ;
  }

  WiFi.softAP(ssid, password);

  Serial.println("Access Point is running!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP-address: ");
  Serial.println(WiFi.softAPIP());

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("AccessPoint is 1");
  display.print("SSID:");
  display.println(ssid);
  display.print("IP:");
  display.println(WiFi.softAPIP());
  display.display();

  server.on("/", handleRoot);
  server.begin();
}

void ws_loop() { server.handleClient(); }
