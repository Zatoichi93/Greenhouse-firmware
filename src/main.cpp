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
StaticJsonBuffer<100> jsonBuffer;

float temperature;
float humidity;
unsigned long timer;
unsigned long totalTime;
unsigned long heatTime;
unsigned long offTime;


void getConfig(){
    JsonObject& root = jsonBuffer.createObject();
    root["maxTemp"] = heater.getMaxTemp();
    root["targetTemp"] = heater.getTargetTemp();

    root.printTo(Serial);
    Serial.println();
    jsonBuffer.clear();
}

void getValues(){
    JsonObject& root = jsonBuffer.createObject();
    root["t"] = temperature;
    root["h"] = humidity;
    root["l"] = light.isOn();
    root["s"] = soil.getAvg();
    root["tt"] = round((millis()-totalTime)/100)/10.0;
    root["ht"] = round((millis()-offTime)/100)/10.0;

    root.printTo(Serial);
    Serial.println();
    jsonBuffer.clear();
    totalTime = millis();
    offTime = millis();
    heatTime = 0;
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

    totalTime = 0;
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
    bool on = heater.heat(temperature);
    if(on){
        heatTime = millis()-totalTime;
    }else{
        offTime = millis()-heatTime;
    }

    sCmd.readSerial();
}
