//#####   LIBRARIES   ######
//GENERAL
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
//OWN
#include <mqtt.hpp>
#include <sensor_handle.cpp>

//######   VARIABLES   ######
//PINOUT
#define TURBIDITY_PIN 36
#define LED_PIN = 16
//WIFI
const char* ssid = "mynet";
const char* pass = "abc123456";
WiFiClient espClient;
