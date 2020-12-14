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
        request->send(200, "application/json", "{\"ID\":\"uc1\"}");
    });
    server.on("/2/Pair", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"ID\":\"uc2\"}");
    });
    server.on("/3/Pair", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"ID\":\"uc3\"}");
    });

    // /GetData Routes
    server.on("/1/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(300, 330);
        request->send(200, "application/json", "{\"ID\":\"uc1\", \"Measure\" :" + String(val) + "}");
    });
    server.on("/2/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(410, 441);
        request->send(200, "application/json", "{\"ID\":\"uc2\", \"Measure\" :" + String(val) + "}");
    });
    server.on("/3/GetData", HTTP_GET, [] (AsyncWebServerRequest *request) {
        int val = random(30, 33);
        
        request->send(200, "application/json", ("{\"ID\":\"uc3\", \"Measure\" :" + String(val) + "}"));
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
  //nothing here
}
