#pragma once

#include <iostream>
#include <string>

class ESP32_Program
{

private:
    void* handle = nullptr;
    bool connected = false;
    bool ledOn = false;

public: 

    ~ESP32_Program();
    bool connect(const std::string& port);
    
    void setLed(bool On);
    void disconnect();


    bool isConnected();

};