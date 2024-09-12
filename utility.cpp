#include <direct.h>
#include "utility.h"

std::string IMAGE_MET_ICO = "\\images\\MET.ico";

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
        return nullptr;
    }
}

std::string get_image_path(std::string file_name) 
{
    std::string path = get_current_path();
    if (path.empty() || file_name.empty())
        return nullptr;
    std::cout << "get image from " << get_current_path() + file_name << '\n';
    return get_current_path() + file_name;
}
