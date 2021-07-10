#pragma once

#include <string>
#include <unordered_map>
#include <map>

extern int CURRENT_LINE;
extern const int INSTRUCTION_SIZE;

namespace symbols {
    // predefined symbols
    extern std::unordered_map< std::string, int > predefined;

    // labels
    extern std::map< std::string, int > labels;

    // labels
    extern std::map< std::string, int > variables;

    // current variable count
    extern int CURRENT_VARIABLE_ADDRESS;
}