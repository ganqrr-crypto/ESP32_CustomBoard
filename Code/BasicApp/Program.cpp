#include "Program.hpp"
#include <iostream>
#include "windows.h"


ESP32_Program::~ESP32_Program(){disconnect();}

bool ESP32_Program::connect(const std::string& port){

    std::cout << "Connecting.." << std::endl;

    std::string path = "\\\\.\\" + port;
    HANDLE h = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, nullptr);
    if(h == INVALID_HANDLE_VALUE) return false;

    DCB dcb{};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(h, &dcb);
    dcb.BaudRate = 115200;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(h, &dcb);

    COMMTIMEOUTS timeouts{};
    timeouts.WriteTotalTimeoutConstant = 50;
    SetCommTimeouts(h, &timeouts);

    handle = h;
    connected = true;
    return true;

}


void ESP32_Program::disconnect(){

    if(handle) CloseHandle((HANDLE)handle);
    handle = nullptr;
    connected = false;

    std::cout << "Disconnected" << std::endl;

}



void ESP32_Program::setLed(bool On){

    if(!connected)
    return;

    char c = On ? '1' : '0';
    DWORD written = 0;
    if(WriteFile((HANDLE)handle, &c, 1, &written, nullptr)) ledOn = On;
  


}

bool ESP32_Program::isConnected(){

    return connected;

}