
#ifndef Light_h
#define Light_h

#include <Arduino.h>

class Light
{
    public:
        Light();
        void turnOn();
        void turnOff();
        bool isOn();
    private:
        bool _isOn;
};

#endif