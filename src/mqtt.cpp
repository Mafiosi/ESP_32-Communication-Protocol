//######   LIBRARIES   ######
#include <mqtt.hpp>


//######   FUNCTIONS   ######
//SETUP
void setupMqqt(){
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

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
