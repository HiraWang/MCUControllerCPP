#ifndef DEVICE_H
#define DEVICE_H

#include <windows.h>
#include <iostream>

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
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void read(char* buf, const DWORD size) = 0;
    virtual void write(char* buf, const DWORD size) = 0;
};

class DeviceG1B : public SerialPort
{
public:
    DeviceG1B(const wchar_t* port_name,
              DWORD baud_rate,
              BYTE byte_size,
              BYTE stop_bits,
              BYTE parity);
    ~DeviceG1B();
    virtual void open() override;
    virtual void close() override;
    virtual void read(char* buf, const DWORD size) override;
    virtual void write(char* buf, const DWORD size) override;
};

#endif