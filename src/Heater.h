
#ifndef Heater_h
#define Heater_h

#include <Arduino.h>
#include <Configuration.h>

class Heater{
    public:
    Heater();
    void setMaxTemperature(float temp);
    void setTargetTemperature(float temp);
    float getMaxTemp();
    float getTargetTemp();
    void heat(float chamberTemp);
    private:
    float _targetTemp;
    float _maxTemp;
    float readTemp();
};

#endif