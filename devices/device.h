#ifndef DEVICE_H
#define DEVICE_H

#include <windows.h>
#include <iostream>

#include "utility.h"

typedef enum {
    AUTOMATION,
    G1B,
    REGLO_ICC
} Device;

class SerialPort
{
public:
    SerialPort(const wchar_t* port_name,
               DWORD baud_rate,
               BYTE byte_size,
               BYTE stop_bits,
               BYTE parity);
    virtual ~SerialPort();
    const wchar_t* port_name;
    HANDLE serial_handle;
    DWORD baud_rate;
    BYTE byte_size;
    BYTE stop_bits;
    BYTE parity;
    virtual SerialCode open() = 0;
    virtual SerialCode close() = 0;
    virtual SerialCode read() = 0;
    virtual SerialCode write() = 0;
};

class DeviceG1B : public SerialPort
{
public:
    DeviceG1B(const wchar_t* port_name,
              DWORD baud_rate,
              BYTE byte_size,
              BYTE stop_bits,
              BYTE parity);
    virtual ~DeviceG1B();
    virtual SerialCode open() override;
    virtual SerialCode close() override;
    virtual SerialCode read() override;
    virtual SerialCode write() override;
};

#endif