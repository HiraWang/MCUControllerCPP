#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

static std::string IMAGE_MET_ICO = "\\images\\MET.ico";

std::string get_separator();
std::string get_current_path();
std::string get_image_path(std::string file_name);

#endif