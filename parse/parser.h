#pragma once

#include <string>
#include <unordered_map>



namespace parser {
    // maps
    extern std::unordered_map< std::string, std::string  > dest_map;
    extern std::unordered_map< std::string, std::string  > comp_map;
    extern std::unordered_map< std::string, std::string  > jump_map;

    // functions
    std::string aInstruction(std::string);
    std::string cInstruction(std::string);
    std::string instruction(std::string);
}