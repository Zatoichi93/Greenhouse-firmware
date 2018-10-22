#include <Soil.h>
#include <Arduino.h>
#include <Configuration.h>

Soil::Soil(){

}

int Soil::getAvg(){
     //Leggiamo il primo sensore
    int rawValue1 = analogRead(SOIL_SENSOR_1_PIN);
    int rawValue2 = analogRead(SOIL_SENSOR_2_PIN);

    int value1=map(rawValue1,SOIL_SENSOR_1_MAX,SOIL_SENSOR_1_MIN,0,100);
    int value2 = map(rawValue2,SOIL_SENSOR_2_MAX,SOIL_SENSOR_2_MIN,0,100);

    return (value1+value2)/2;
}

int Soil::getValue(int i){
   
}