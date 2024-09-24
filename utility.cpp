#include <direct.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utility.h"
#include "widgets/msg_subwindow.h"

using json = nlohmann::json;

std::string IMAGE_MET_CLOSE = "\\images\\Close.png";
std::string IMAGE_MET_ERROR = "\\images\\Error.png";
std::string IMAGE_MET_EXIT = "\\images\\Exit.png";
std::string IMAGE_MET_FULL_SCREEN = "\\images\\FullScreen.png";
std::string IMAGE_MET_ICO = "\\images\\MET.ico";
std::string IMAGE_MET_LOAD = "\\images\\Load.png";
std::string IMAGE_MET_MAX_SIZE = "\\images\\MaxSize.png";
std::string IMAGE_MET_MENU = "\\images\\Menu.png";
std::string IMAGE_MET_POWER = "\\images\\Power.png";

std::string CONFIG_MET = "\\configuration\\config.json";


std::string get_separator() 
{
#ifdef _WIN32
    std::string separator("\\");
#else
    std::string separator("/");
#endif
    return separator;
}

std::string get_current_path() 
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

std::string get_abs_path(std::string file_name) 
{
    std::string path = get_current_path();
    if (path.empty() || file_name.empty())
        return std::string();
    std::cout << "get path : " << get_current_path() + file_name << '\n';
    return get_current_path() + file_name;
}

METPara::METPara()
{
    num = 0;
    str = "";
    is_editable = false;
}

METPara::~METPara()
{

}

void METPara::reset()
{
    num = 0;
    str = "";
    is_editable = false;
}

METParaList::METParaList() : 
    list(nullptr)
{
    load_json_file();
}

METParaList::~METParaList()
{
    delete[] list;
}

void METParaList::load_json_file()
{
    // load data from json configuration file
    std::ifstream f(get_abs_path(CONFIG_MET));
    if (f.fail()) {
        METMsgSubwindow("config file not found");
        exit(PROGRAM_NO_CONFIG);
    }

    json data = json::parse(f);
    size = data.size();
    if (!list) {
        std::cout << "create new list of met para" << '\n';
        list = new METPara[size];
    } else {
        std::cout << "reset the list of met para" << '\n';
        for (int id = 0; id < size; id++) {
            list[id].reset();
        }
    }

    // Insert data to METParaList 
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
}