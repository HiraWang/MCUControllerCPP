#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

typedef enum {
    DEFAULT = false,
    PRESSED = true
} Status;

std::string get_separator();
std::string get_current_path();
std::string get_image_abs_path(std::string file_name);

#endif