#include <Arduino.h>
#include <Heater.h>
#include <Configuration.h>
#include <EEPROM.h>
#include <Thermistor.h>

THERMISTOR _thermistor(NTC_PIN,NTC_NOMINAL,NTC_BETA,NTC_PULLUP);
float temp;
unsigned long currentTime;
int _maxTempADDR=0;
int _tgtTempADDR=8;

Heater::Heater(){
    EEPROM.get(_maxTempADDR,_maxTemp);
    EEPROM.get(_tgtTempADDR,_targetTemp);
    pinMode(HEATHER_PIN,OUTPUT);

    if(_maxTemp <0 || _maxTemp>50) _maxTemp = 0;
    if(_targetTemp<0 || _targetTemp>40) _targetTemp = 0; 
}

void Heater::setMaxTemperature(float temp){
    _maxTemp = temp;
    EEPROM.put(_maxTempADDR,_maxTemp);
}

void Heater::setTargetTemperature(float temp){
    _targetTemp = temp;
    EEPROM.put(_tgtTempADDR,_targetTemp);
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
    else if(readTemp()>_maxTemp){
        //Spegne
        digitalWrite(HEATHER_PIN,LOW);
    }

}