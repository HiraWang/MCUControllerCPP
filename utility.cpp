#include <direct.h>

#include "utility.h"

std::string IMAGE_MET_ICO = "\\images\\MET.ico";
std::string IMAGE_MET_POWER = "\\images\\Power.png";
std::string IMAGE_MET_MAX_SIZE = "\\images\\MaxSize.png";
std::string IMAGE_MET_FULL_SCREEN = "\\images\\FullScreen.png";

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

std::string get_image_abs_path(std::string file_name) 
{
    std::string path = get_current_path();
    if (path.empty() || file_name.empty())
        return std::string();
    std::cout << "get image from " << get_current_path() + file_name << '\n';
    return get_current_path() + file_name;
}
