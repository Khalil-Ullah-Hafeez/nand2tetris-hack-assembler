#include <string>
#include <unordered_map>
#include <map>

#include "symbols.h"

int CURRENT_LINE = 0;
const int INSTRUCTION_SIZE = 16;

namespace symbols {
    // predefined symbols
    std::unordered_map< std::string, int > predefined = {
        {"R0",         0},
        {"R1",         1},
        {"R2",         2},
        {"R3",         3},
        {"R4",         4},
        {"R5",         5},
        {"R6",         6},
        {"R7",         7},
        {"R8",         8},
        {"R9",         9},
        {"R10",       10},
        {"R11",       11},
        {"R12",       12},
        {"R13",       13},
        {"R14",       14},
        {"R15",       15},
        {"SCREEN", 16384},
        {"KBD",    24576}
    };

    // labels
    std::map< std::string, int > labels;

    // variables
    std::map< std::string, int > variables;

    // current variable count
    int CURRENT_VARIABLE_ADDRESS = 16;
}