#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

std::string get_separator();
std::string get_current_path();
std::string get_abs_path(std::string file_name);

typedef enum {
    DEFAULT = false,
    PRESSED = true
} Status;

typedef enum {
    OK = 0,
    NO_CONFIG = 1
} ExitCode;

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
    ~METPara();
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
    ~METParaList();
    size_t size;
    METPara* list;
    void load_json_file();
};

#endif