#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

std::string get_separator();
std::string get_current_path();
std::string get_abs_path(std::string file_name);

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

class METPara
{
public:
    METPara();
    virtual ~METPara();
    bool is_editable;
    int num;
    std::string str;
    std::string name;
    void reset();
};

class METParaList
{
public:
    METParaList();
    virtual ~METParaList();
    size_t size;
    METPara* list;
    ExitCode load_json_file();
};

#endif