#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

#define MONITOR_CHUNK_SIZE (4096)
#define MONITOR_BUFFER_SIZE (MONITOR_CHUNK_SIZE * 2) 

typedef enum {
    BUTTON_DEFAULT = false,
    BUTTON_PRESSED = true
} ButtonStatus;

typedef enum {
    PROGRAM_OK = 0,
    PROGRAM_NO_CONFIG = 1
} ExitCode;

typedef enum {
    SERIAL_OK = 0,
    SERIAL_FAIL = 1,
    SERIAL_NO_PORT = 2,
    SERIAL_FAIL_TO_GET_STATE = 3,
    SERIAL_FAIL_TO_SET_STATE = 4,
    SERIAL_FAIL_TO_SET_TIMEOUT = 5,
    SERIAL_FAIL_TO_READ = 6,
    SERIAL_FAIL_TO_WRITE = 7
} SerialCode;

typedef enum {
    BAUDRATE = 0,
    BUFFER_SIZE,
    BYTESIZE,
    CHUNKS_PER_SCENE,
    MONITOR_KEYWORD,
    OFFSET,
    PARITY,
    PERIOD_MAX,
    PULSE_GEN_ID,
    PULSE_GEN_KEYWORD,
    PULSE_GEN_PASSWORD,
    PUMP_KEYWORD,
    STOPBITS,
    TIMER_PERIOD
} ParaID;

char* CopyStringToNewedCharArray(const std::string& str);
std::string GetSeparator();
std::string GetCurrentPath();
std::string GetAbsPath(std::string file_name);
std::string GetSerialCodeInfo(SerialCode code);
void HideConsole();
void ShowConsole();
void ResizeConsole(int w, int h);
void ShowSerialCodeInfo(SerialCode code);

class MetPara
{
public:
    MetPara();
    virtual ~MetPara();
    void Reset();
    bool is_editable;
    int num;
    std::string str;
    std::string name;
};

class MetParaList
{
public:
    MetParaList();
    MetParaList(const MetParaList& source);
    void operator = (const MetParaList& source);
    virtual ~MetParaList();
    ExitCode LoadJsonFile();
    size_t size;
    MetPara* list;
};

#endif