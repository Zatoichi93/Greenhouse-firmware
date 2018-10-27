#include <Soil.h>
#include <Arduino.h>
#include <Configuration.h>

Soil::Soil(){
    pinMode(SOIL_POWER_PIN,OUTPUT);
}

int Soil::getAvg(){
    digitalWrite(SOIL_POWER_PIN,HIGH);
    delay(10);
    int rawValue1 = analogRead(SOIL_SENSOR_1_PIN);
    int rawValue2 = analogRead(SOIL_SENSOR_2_PIN);
    digitalWrite(SOIL_POWER_PIN,LOW);

    int value1= map(rawValue1,SOIL_SENSOR_1_MIN,SOIL_SENSOR_1_MAX,0,100);
    int value2 = map(rawValue2,SOIL_SENSOR_2_MIN,SOIL_SENSOR_2_MAX,0,100);

    return (value1+value2)/2;
}