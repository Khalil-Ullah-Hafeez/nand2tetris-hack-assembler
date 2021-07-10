#include <iostream>

#include "helper.h"

namespace helper {
    // check if line is number
    bool checkNum(std::string line) {
        bool result = true;
        for(int i = 0; i < line.size(); i++) {
            if(!isdigit(line[i])) {
                result = false;
                break;
            }
        }    
        return result;
    }
    
    // check if the line is an instruction
    bool checkValid(std::string line) {
        bool result = true;

        // check if line is empty
        if (line == "" || line == "\n") {
            result = false;
            return result;
        }
        
        // check if // exists in line
        if (line.rfind("//", 0) == 0) {
            result = false;
            return result;
        }

        // check if /* exists in line
        if (line.rfind("/*", 0) == 0) {
            result = false;
            return result;
        }

        // check if * exists in line
        if (line.rfind("*", 0) == 0) {
            result = false;
            return result;
        }

        /// check if /* exists in line
        if (line.rfind("*/", 0) == 0) {
            result = false;
            return result;
        }


        return result;
    }

    // remove inline comments from the line
    std::string removeInlineComment(std::string line) {
        if (line.find("//") != std::string::npos) {
            line = line.substr(0, line.find("//"));
        }
        if ((line.find("/*") != std::string::npos) && (line.find("*/") != std::string::npos)) {
            std::string comment = line.substr(line.find("/*"), line.find("*/"));
            int starting_position = line.find("/*");
            line = line.erase(starting_position, comment.length());
        }
        return line;
    }
}