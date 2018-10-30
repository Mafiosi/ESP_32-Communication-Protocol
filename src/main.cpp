//######   LIBRARIES   ######
#include <general.hpp>


//######   FUNCTIONS   ######
void setupWifi(){
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

void setupPin(){
    pinMode(ledPin, OUTPUT);
}


//######   MAIN SETUP   ######
void setup() {
    Serial.begin(115200);
    setupPin();
    setupWifi();
    setupMqtt();
    delay(1000);
}


//######   MAIN LOOP   ######
void loop() {

    //Print Value of Sensor
    float turbval = readvalue(TURBIDITY_PIN);
    float turbres  = mathturb(turb);

    //Test Mqtt
    check_mqtt_conn();
    publish(8);

    delay(2000);

}
