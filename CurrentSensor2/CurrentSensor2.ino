#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
AsyncWebServer server(80);

const char* ssid = "";
const char* password = "";


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "application/json", "{\"message\":\"Nothing here\"}");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // /Pair Routes
    server.on("/1/Pair", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"ID\":\"uc4\"}");
    });
    server.on("/2/Pair", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"ID\":\"gn1\"}");
    });
    server.on("/3/Pair", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"ID\":\"mnt\"}");
    });

    // /GetData Routes
    // 1 = Consumer
    server.on("/1/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(500, 550);
        request->send(200, "application/json", "{\"ID\":\"uc4\", \"Measure\" :" + String(val) + "}");
    });
    //2 = Generator
    server.on("/2/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(450, 1800);
        request->send(200, "application/json", "{\"ID\":\"gn1\", \"Measure\" :" + String(val) + "}");
    });
    //3 = Monitor
    server.on("/3/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(80, 100);
        
        request->send(200, "application/json", ("{\"ID\":\"mnt\", \"Measure\" :" + String(val) + "}"));
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
  //nothing here
}
