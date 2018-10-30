//######   LIBRARIES   ######
#include <general.hpp>


//######   VARIABLES   ######
const char* brokerUser = "jbeleza.tr@gmail.com";
const char* brokerPass = "6ec21d8d";
const char* broker = "mqtt.dioty.co";
const char* outTopic = "/jbeleza.tr@gmail.com/out";
const char* inTopic = "/jbeleza.tr@gmail.com/in";
PubSubClient client(espClient);


//######   FUNCTIONS   ######
void setupMqtt();
void check_mqtt_conn();
void callback(char* topic, byte* payload, unsigned int length);
void publish();
