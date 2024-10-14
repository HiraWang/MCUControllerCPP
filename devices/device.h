#ifndef DEVICE_H
#define DEVICE_H

#include <windows.h>
#include <iostream>
#include <QObject>

#include "utility.h"

#define CHUNK_SIZE (4096)
#define BUFFER_SIZE (CHUNK_SIZE * 2) 

typedef enum {
    AUTOMATION,
    G1B,
    REGLO_ICC,
    MONITOR
} Device;

class SerialPort : public QObject
{
    Q_OBJECT

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
    virtual SerialCode Login() = 0;
    BYTE byte_size;
    BYTE stop_bits;
    BYTE parity;
    DWORD baud_rate;
    HANDLE serial_handle;
    const wchar_t* port_name;
};

class DeviceG1B : public SerialPort
{
    Q_OBJECT

public:
    DeviceG1B(const wchar_t* port_name,
              DWORD baud_rate,
              BYTE byte_size,
              BYTE stop_bits,
              BYTE parity);
    virtual ~DeviceG1B();
    virtual SerialCode Open() override;  // override
    virtual SerialCode Close() override; // override
    virtual SerialCode Read() override;  // override
    virtual SerialCode Write() override; // override
    virtual SerialCode Login() override; // override
    SerialCode Read(char* buf, const int size); // overload
    SerialCode Write(const char* buf);          // overload
    SerialCode SetFreq(int freq);
    SerialCode SetPulseWidth(float pw);
    SerialCode SetVoltage(int v);
    SerialCode SetOffset(int offset);
    SerialCode On();
    SerialCode Off();

signals:
    void SignalLoginFailed(void);
    void SignalLoginFinished(void);

private:
    SerialCode LoginStepFunction(std::string name,
                                 std::string input,
                                 const char* keyword,
                                 int max_cnt,
                                 DWORD time_delay);
};

class DeviceRegloIcc : public SerialPort
{
public:
    DeviceRegloIcc(const wchar_t* port_name,
                   DWORD baud_rate,
                   BYTE byte_size,
                   BYTE stop_bits,
                   BYTE parity);
    virtual ~DeviceRegloIcc();
    virtual SerialCode Open() override;  // override
    virtual SerialCode Close() override; // override
    virtual SerialCode Read() override;  // override
    virtual SerialCode Write() override; // override
    virtual SerialCode Login() override; // override
    SerialCode SetRpm(BYTE channel, float rpm);
    SerialCode SetCw(BYTE channel);
    SerialCode SetCcw(BYTE channel);
    SerialCode On(BYTE channel);
    SerialCode Off(BYTE channel);

private:
    SerialCode SetAddress();
    SerialCode SetRpmMode(BYTE channel);
};

class DeviceArduinoDue : public SerialPort
{
public:
    DeviceArduinoDue(const wchar_t* port_name,
                     DWORD baud_rate,
                     BYTE byte_size,
                     BYTE stop_bits,
                     BYTE parity);
    virtual ~DeviceArduinoDue();
    virtual SerialCode Open() override;  // override
    virtual SerialCode Close() override; // override
    virtual SerialCode Read() override;  // override
    virtual SerialCode Write() override; // override
    virtual SerialCode Login() override; // override
    SerialCode ReadBufferAndSave();
    size_t count;
    const int chunk_size = CHUNK_SIZE;
    const int buffer_size = BUFFER_SIZE;
};

#endif