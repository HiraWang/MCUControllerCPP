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
    virtual SerialCode Open() = 0;
    virtual SerialCode Close() = 0;
    virtual SerialCode Read() = 0;
    virtual SerialCode Write() = 0;
    BYTE byte_size;
    BYTE stop_bits;
    BYTE parity;
    DWORD baud_rate;
    HANDLE serial_handle;
    const wchar_t* port_name;
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
    virtual SerialCode Open() override;
    virtual SerialCode Close() override;
    virtual SerialCode Read() override;
    virtual SerialCode Write() override;
};

#endif