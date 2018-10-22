#include <Arduino.h>
#include <ArduinoJson.h>
#include <SerialCommand.h>
#include <SimpleDHT.h>
#include <Light.h>
#include <Heater.h>
#include <Soil.h>

SerialCommand sCmd;
SimpleDHT22 dht22(DHT22_PIN);
Light light;
Heater heater;
Soil soil;

float temperature;
float humidity;
unsigned long timer;

void getConfig(){
    StaticJsonBuffer<100> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root["maxTemp"] = heater.getMaxTemp();
    root["targetTemp"] = heater.getTargetTemp();

    root.printTo(Serial);
    Serial.println();
}

void getValues(){
    
    StaticJsonBuffer<100> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    root["temp"] = temperature;
    root["humidity"] = humidity;
    root["light"] = light.isOn();
    root["soil"] = soil.getAvg();

    root.printTo(Serial);
    Serial.println();
}

void processSetCmd(){char *arg;
    arg = sCmd.next();
    float temp = atof(sCmd.next());
    Serial.println(temp);
    if(strcmp(arg,"M")==0){
        heater.setMaxTemperature(temp);
    }
    else if(strcmp(arg,"T")==0){
        heater.setTargetTemperature(temp);
    }
}

void turnOn(){
    light.turnOn();
}

void turnOff(){
    light.turnOff();
}

void setup() {
    Serial.begin(9600);

    sCmd.addCommand("ON", turnOn);
    sCmd.addCommand("OFF", turnOff);
    sCmd.addCommand("SET", processSetCmd);
    sCmd.addCommand("GET", getConfig);
    sCmd.addCommand("READ", getValues);

}

void loop() {
    if(millis()-timer > 2000){
        int err = SimpleDHTErrSuccess;
        if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
            temperature=1000;
            humidity = 1000;
        }
        timer = millis();
    }
    heater.heat(temperature);
    sCmd.readSerial();
}
