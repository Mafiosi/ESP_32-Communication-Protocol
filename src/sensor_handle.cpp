//######   LIBRARIES   ######
#include <sensor_handle.hpp>


//######   FUNCTIONS   ######
//READ SENSOR VALUE
float readvalue(int sensor_id){
    float sensorValue = analogRead(sensor_ID);
    return sensorValue;
}

//TURBIDITY SENSOR CALCULOUS
float turbmath(float sensorvalue){
    float ardval = val*0.00488758553;                       //ARDUINO VALUE UNITS
    float ntu_val = ((ardval)/((5000/ardval)-10000))*70000; //Current * 70000
    return ntu_val;

}
