#include <Arduino.h>
#include <Heater.h>
#include <Configuration.h>
#include <Thermistor.h>

THERMISTOR _thermistor(NTC_PIN,NTC_NOMINAL,NTC_BETA,NTC_PULLUP);

Heater::Heater(){
    _maxTemp=0;
    _targetTemp =0;
    pinMode(HEATHER_PIN,OUTPUT);
}

void Heater::setMaxTemperature(float temp){
    _maxTemp = temp;
}

void Heater::setTargetTemperature(float temp){
    _targetTemp = temp;
}

float Heater::getMaxTemp(){
    return _maxTemp;
}

float Heater::getTargetTemp(){
    return _targetTemp;
}

float Heater::readTemp(){
    return _thermistor.read();
}

void Heater::heat(float chamberTemp){
    if(readTemp()<=_maxTemp && chamberTemp<_targetTemp){
        //Accende il riscaldamento
        digitalWrite(HEATHER_PIN,HIGH);
    }
    else{
        //Spegne
        digitalWrite(HEATHER_PIN,LOW);
    }

}