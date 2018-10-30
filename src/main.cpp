//######   LIBRARIES   ######
//GENERAL
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


//######   VARIABLES   ######
//PINOUT
#define TURBIDITY_PIN 36
#define LEDPIN 16
//WiFi
WiFiClient espClient;
//MQTT
const char* brokerUser = "jbeleza.tr@gmail.com";
const char* brokerPass = "6ec21d8d";
const char* broker = "mqtt.dioty.co";
const char* outTopic = "/jbeleza.tr@gmail.com/out";
const char* inTopic = "/jbeleza.tr@gmail.com/in";
PubSubClient client(espClient);


//######   FUNCTIONS   ######
//##  GENERAL  ##
//Connect to Wifi
void setupWifi(){
    const char* ssid = "mynet";
    const char* pass = "abc123456";
    delay(100);
    Serial.print("\nConnecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while(WiFi.status() != WL_CONNECTED){
        delay(100);
        Serial.print("-");
    }

    Serial.print("\nConnected");
    Serial.print(ssid);
}

//Setup Pin Connection
void setupPin(){
    pinMode(LEDPIN, OUTPUT);
}

//##  MQTT  ##

//Check Mqtt Connection
void check_mqtt_conn(){
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

//Receive Data (Subscriber)
void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Received message: ");
    Serial.println(topic);
    for(int i=0; i<length; i++){
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

//Send Data (Publisher)
void publish(int value){
    char messages[50];
    client.loop();
    snprintf(messages, 75, "Value: %ld", value);
    client.publish(outTopic, messages);
}

//Setup MQTT
void setupmqqt(){
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

//##  SENSOR  ##
//Read Sensor Value
float readvalue(int sensor_id){
    float sensorValue = analogRead(sensor_id);
    return sensorValue;
}

//Math To Turbidity - V to NTU
float turbmath(float sensorvalue){
    float ardval = sensorvalue*0.00488758553;                       //ARDUINO VALUE UNITS
    float ntu_val = ((ardval)/((5000/ardval)-10000))*70000; //Current * 70000
    return ntu_val;
}

//######   MAIN SETUP   ######
void setup() {
    Serial.begin(115200);
    setupPin();
    setupWifi();
    setupmqqt();
    delay(1000);
}


//######   MAIN LOOP   ######
void loop() {

    //Print Value of Sensor
    float turbval = readvalue(TURBIDITY_PIN);
    float turbres  = turbmath(turbval);

    //Test Mqtt
    check_mqtt_conn();
    publish(8);

    delay(2000);

}
