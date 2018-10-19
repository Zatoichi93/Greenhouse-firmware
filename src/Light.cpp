#include <Light.h>
#include <Arduino.h>
#include <Configuration.h>

Light::Light(){
    _isOn = false;
    pinMode(LIGHT_PIN,OUTPUT);
}

void Light::turnOn(){
    digitalWrite(LIGHT_PIN,HIGH);
    _isOn = true;
}

void Light::turnOff(){
    digitalWrite(LIGHT_PIN,LOW);
    _isOn = false;
}

bool Light::isOn(){
    return _isOn;
}