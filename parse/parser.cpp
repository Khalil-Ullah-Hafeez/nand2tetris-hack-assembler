#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "parser.h"
#include "../helper/helper.h"
#include "../symbols/symbols.h"

namespace parser {

    // destination map
    std::unordered_map< std::string, std::string  > dest_map = {
        {"null",    "000"},
        {"M",       "001"},
        {"D",       "010"},
        {"MD",      "011"},
        {"A",       "100"},
        {"AM",      "101"},
        {"AD",      "110"},
        {"AMD",     "111"},
    };

    // computation map
    std::unordered_map< std::string, std::string  > comp_map = {
        // computation pairs if a == 0
        {"0",   "0101010"},
        {"1",   "0111111"},
        {"-1",  "0111010"},
        {"D",   "0001100"},
        {"A",   "0110000"},
        {"!D",  "0001101"},
        {"!A",  "0110001"},
        {"-D",  "0001111"},
        {"-A",  "0110011"},
        {"D+1", "0111111"},
        {"A+1", "0110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"D+A", "0000010"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},
        // computation pairs if a == 1
        {"M",   "1110000"},
        {"!M",  "1110001"},
        {"-M",  "1110011"},
        {"M+1", "1110111"},
        {"M-1", "1110010"},
        {"D+M", "1000010"},
        {"M+D", "1000010"},
        {"D-M", "1010011"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
    };

    // jump map
    std::unordered_map< std::string, std::string  > jump_map = {
        {"null",    "000"},
        {"JGT",     "001"},
        {"JEQ",     "010"},
        {"JGE",     "011"},
        {"JLT",     "100"},
        {"JNE",     "101"},
        {"JLE",     "110"},
        {"JMP",     "111"},
    };

    // determine the type of instruction and call respective parsing function
    std::string instruction(std::string line) {    
        char first_character = line[0];

        if (first_character == '@') {
            // A instruction
            return aInstruction(line);
        } else if (first_character == '(') {
            // label declaration
            CURRENT_LINE--;
            return "";
        } else {
            // C instruction
            return cInstruction(line);
        }
    }

    // parse A instruction and return the binary in std::string
    std::string aInstruction(std::string line) {
        // remove first letter
        line = line.substr(1, line.size() - 1);

        std::string binary_converted = "";

        // if operand is a number then convert it to binary and return
        if (helper::checkNum(line)) {
            binary_converted = std::bitset<16>(stoi(line)).to_string();
            return binary_converted;
        }

        // try to find the operand in the label or variable map, throw exception if failed
        try {    
            binary_converted = std::bitset<16>(symbols::predefined.at(line)).to_string();
        } catch (const std::out_of_range& err) {
            try {
                binary_converted = std::bitset<16>(symbols::variables.at(line)).to_string();
            } catch (const std::out_of_range& err) {
                try {
                    binary_converted = std::bitset<16>(symbols::labels.at(line)).to_string();
                } catch (const std::out_of_range& err) {
                    throw ("An error has occured");
                }
            }
        }

        return binary_converted;
    }

    // parse C instruction and return the binary in std::string
    std::string cInstruction(std::string line) {
        std::string result = "111";

        std::string dest = "";
        std::string comp = "";
        std::string jump = "";

        // get the destination part of instruction if = exists in line
        if (line.find('=') != std::string::npos) {
            dest = line.substr(0, line.find('='));

            // get the computation part if there is no ; in line
            if (line.find(';') == std::string::npos)
                comp = line.substr(line.find('=')+1, line.size()-1);
            // if false then = and ; exist in line
            else {
                comp = line.substr(line.find('=')+1, line.find(";") - line.find("=") - 1);
                jump = line.substr(line.find(';')+1, line.size()-1);
            }

        } 
        // if false then destination part does not exist in line
        else {
            // get the computation part in line
            if (line.find(';') != std::string::npos) {
                comp = line.substr(0, line.find(';'));

                // get the jump part in line
                jump = line.substr(line.find(';')+1, line.size()-1);
            }
            // if false, then the structure of instruction is wrong. throw an exception.
            else {
                throw ("An error occured.");
            }
        }

        try {
            result += comp_map.at(comp);

            if (dest != "")
                result += dest_map.at(dest);
            else
                result += "000";

            if (jump != "")
                result += jump = jump_map.at(jump);
            else 
                result += "000";
        } catch (const std::out_of_range& err) {
            throw ("An error occured.");
        }

        return result;
    }
}