#include <Arduino.h>
#include <SimpleDHT.h>
#include <Light.h>
#include <Heater.h>

char buffer[20];
Light light;
Heater heater;

void setup() {
    Serial.begin(9600);

}

void loop() {
}

void SerialEvent(){
    if(Serial.available()){
        Serial.readBytesUntil('\n',buffer,20);
        

    }

}
