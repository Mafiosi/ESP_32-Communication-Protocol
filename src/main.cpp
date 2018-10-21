/*
  Blink
*/
#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "abeleza";
const char* pass = "abeleza123456";

void setupWifi(){
    delay(100);
    Serial.print("\Connecting to");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print("-");
    }

    Serial.print("\nConnected");
    Serial.print(ssid);

}

void setup() {
    Serial.print(115200);
    setupWifi();
}

void loop() {
}
