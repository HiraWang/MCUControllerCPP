#include "utility.h"

#include <direct.h>
#include <Windows.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool g_normal = true;
bool g_ui_test = !g_normal;

std::string LF = "\n";
std::string CR = "\r";
std::string IMAGE_MET_CLOSE = "\\images\\Close.png";
std::string IMAGE_MET_CONSOLE = "\\images\\Console.png";
std::string IMAGE_MET_DOWN = "\\images\\Down.png";
std::string IMAGE_MET_ERROR = "\\images\\Error.png";
std::string IMAGE_MET_EXIT = "\\images\\Exit.png";
std::string IMAGE_MET_FULL_SCREEN = "\\images\\FullScreen.png";
std::string IMAGE_MET_ICO = "\\images\\MET.ico";
std::string IMAGE_MET_LEFT = "\\images\\Left.png";
std::string IMAGE_MET_LOAD = "\\images\\Load.png";
std::string IMAGE_MET_LOADING = "\\images\\Loading.gif";
std::string IMAGE_MET_MAX_SIZE = "\\images\\MaxSize.png";
std::string IMAGE_MET_MENU = "\\images\\Menu.png";
std::string IMAGE_MET_MINUS = "\\images\\Minus.png";
std::string IMAGE_MET_PLUS = "\\images\\Plus.png";
std::string IMAGE_MET_POWER = "\\images\\Power.png";
std::string IMAGE_MET_RIGHT = "\\images\\Right.png";
std::string IMAGE_MET_SCAN = "\\images\\Scan.png";
std::string IMAGE_MET_STOP = "\\images\\Stop.png";
std::string IMAGE_MET_UP = "\\images\\Up.png";

std::string CONFIG_MET = "\\configuration\\config.json";

char* CopyStringToNewedCharArray(const std::string& str)
{
    const char* c_str = str.c_str();
    rsize_t size = str.length() + 1;
    char* arr = new char[size];
    strcpy_s(arr, size, c_str);
    //std::cout << arr << '\n';

    return arr;
}

std::string GetSeparator() 
{
#ifdef _WIN32
    std::string separator("\\");
#else
    std::string separator("/");
#endif
    return separator;
}

std::string GetCurrentPath() 
{
    char* buf = nullptr;
    buf = _getcwd(nullptr, 0);
    if (buf) {
        std::string path = buf; // buf is copied to path
        free(buf);
        return path;
    } else {
        return std::string();
    }
}

std::string GetAbsPath(std::string file_name) 
{
    std::string path = GetCurrentPath();
    if (path.empty() || file_name.empty())
        return std::string();
    std::cout << "get path : " << GetCurrentPath() + file_name << '\n';
    return GetCurrentPath() + file_name;
}

void HideConsole()
{
    std::cout << "hide console" << '\n';
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
    std::cout << "show console" << '\n';
    ShowWindow(GetConsoleWindow(), SW_SHOW);
}

void ResizeConsole(int w, int h)
{
    if (w <= 100 || h <= 100) {
        return;
    }
    std::cout << "resize console" << '\n';
    SetWindowPos(GetConsoleWindow(), HWND_TOP, 200, 200, w, h, SWP_HIDEWINDOW);
}

void ShowSerialCodeInfo(SerialCode code)
{
    if (code == SERIAL_OK) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
    }
}

MetPara::MetPara() : 
    is_editable(false),
    num(0),
    str(""),
    name("")
{

}

MetPara::~MetPara()
{

}

void MetPara::Reset()
{
    is_editable = false;
    num = 0;
    str = "";
    name = "";
}

MetParaList::MetParaList() : 
    size(0),
    list(nullptr)
{

}

MetParaList::MetParaList(const MetParaList& source)
{
    this->size = source.size;
    if (this->size >= 0) {
        this->list = new MetPara[this->size];
    } else {
        return;
    }

    for (int id = 0; id < this->size; id++) {
        this->list[id] = source.list[id];
    }
}

void MetParaList::operator = (const MetParaList& source)
{
    this->size = source.size;
    if (this->size >= 0) {
        this->list = new MetPara[this->size];
    } else {
        return;
    }

    for (int id = 0; id < this->size; id++) {
        this->list[id] = source.list[id];
    }
}

MetParaList::~MetParaList()
{
    delete[] list;
}

ExitCode MetParaList::LoadJsonFile()
{
    // load data from json configuration file
    std::ifstream f(GetAbsPath(CONFIG_MET));
    if (f.fail()) {
        return PROGRAM_NO_CONFIG;
    }

    json data = json::parse(f);
    size = data.size();
    if (!list) {
        std::cout << "create new list of met para" << '\n';
        list = new MetPara[size];
    } else {
        std::cout << "reset the list of met para" << '\n';
        for (int id = 0; id < size; id++) {
            list[id].Reset();
        }
    }

    // Insert data to MetParaList 
    int id = 0;
    for (json::iterator it = data.begin(); it != data.end(); ++it, id++) {
        std::cout << std::left << std::setw(20) << it.key() << " : " << it.value();
        list[id].name = it.key();
        if (it.value().is_string()) {
            list[id].str = it.value();
            std::cout << std::right << std::setw(18) << list[id].str << '\n';
        } else if (it.value().is_number()) {
            list[id].num = it.value();
            std::cout << std::right << std::setw(20) << list[id].num << '\n';
        } else {
            std::cout << '\n';
        }
        list[id].is_editable = false;
    }

    return PROGRAM_OK;
}