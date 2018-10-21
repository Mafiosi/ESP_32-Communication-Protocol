/*
  Blink
*/
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "abeleza";
const char* pass = "abeleza123456";
const char* brokerUser = "jbeleza.tr@gmail.com";
const char* brokerPass = "6ec21d8d";
const char* broker = "mqtt.dioty.co";
const char* outTopic = "/jbeleza.tr@gmail.com/out";
const char* inTopic = "/jbeleza.tr@gmail.com/in";

WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime;
int count = 0;
char messages[50];

void setupWifi(){
    delay(100);
    Serial.print("\nConnecting to");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print("-");
    }

    Serial.print("\nConnected");
    Serial.print(ssid);
}

void reconnect(){
    while(!client.connected()){
        Serial.print("\nConnecting to");
        Serial.println(broker);
        if(client.connect("koikoikoi", brokerUser, brokerPass)){
            Serial.print("\nConnected to");
            Serial.println(broker);
            client.subscribe(inTopic);
        } else{
            Serial.println("\nTrying to connect again");
            delay(5000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Received message: ");
    Serial.println(topic);
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
    }
    Serial.println();
}
void setup() {
    Serial.begin(115200);
    setupWifi();
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

void loop() {
    if(!client.connected()){
        reconnect();
    }
    client.loop();

    currentTime = millis();
    if(currentTime - lastTime > 2000){
        count++;
        snprintf(messages, 75, "Count: %ld", count);
        Serial.print("Seding Message: ");
        Serial.println(messages);
        client.publish(outTopic, messages);
        lastTime = millis();
    }


}
