#include <iostream>
#include <string>
#include <stdexcept>

#include "authenticator.h"
#include "../helper/helper.h"
#include "../parse/parser.h"
#include "../symbols/symbols.h"

namespace authenticator {
    
    // determine the type of instruction and call corresponding authentication function
    bool instruction(std::string line) {
        bool result = false;
        char first_character = line[0];

        if (first_character == '@') {
            // A instruction
            if (aInstruction(line)) result = true; 
            else throw ("Operands to A instruction should be valid");

        } else if (first_character == '(') {
            // label declaration            
            if (labelHandler(line)) result = true; 
            else throw ("Label declaration is invalid");
        }
        else {
            // C instruction
            if (cInstruction(line)) result = true; 
            else throw ("C instruction is invalid");
        }

        return result;
    }

    // authenticate A instruction and return false if invalid
    bool aInstruction(std::string line) {
        bool result = true;

        line = line.substr(1, line.size() - 1);
        
        // check if value after @ is a number or not
        if (!helper::checkNum(line)) {
            try {
                symbols::predefined.at(line);
            } catch (const std::out_of_range& err) {
                if (symbols::labels[line] == 0) {
                    symbols::labels[line] = -1;
                }
            }
        }

        return result;
    }

    // add the label to the label map and return false if something goes wrong
    bool labelHandler(std::string line) {

        line = line.substr(1, line.size() - 2);

        if ((line.find(";") != std::string::npos) || 
            (line.find("=") != std::string::npos) || 
            (line.find("@") != std::string::npos)
            )
            return false;

        // add line number as value
        symbols::labels[line] = CURRENT_LINE;

        return true;
    }


    // authenticate C instruction and return false if invalid
    bool cInstruction(std::string line) {
        bool result = true;

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
                result = false;
                return result;
            }
        }

        // verify extracted values with the maps
        try {
            if (dest != "")
                parser::dest_map.at(dest);

            parser::comp_map.at(comp);

            if (jump != "")
                parser::jump_map.at(jump);
        } catch (const std::out_of_range& err) {
            result = false;
            return result;
        }

        return result;
    }


}