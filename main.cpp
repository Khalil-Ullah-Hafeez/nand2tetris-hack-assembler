// 𝐁𝐒𝐄𝐅𝟏𝟗𝐀𝟓𝟑𝟐 - 𝐊𝐇𝐀𝐋𝐈𝐋 𝐔𝐋𝐋𝐀𝐇

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>


#include "./authentication/authenticator.h"
#include "./parse/parser.h"
#include "./helper/helper.h"
#include "./symbols/symbols.h"


void first_pass(std::istream & file_data);
void second_pass(std::istream & file_data, std::ostream & file_output);

int main() {
    

    // inputing file name
    std::string file_name = "";
    
    std::cout << "Enter the name of the file (should be in the same directory) with extension .asm: ";
    std::cin >> file_name;

    // opening the .asm file
    std::ifstream file_data;
    file_data.open(file_name.c_str());

    std::string output_name = file_name.substr(0, file_name.find('.')).append(".hack");

    // opening .hack file
    std::ofstream file_output;
    file_output.open(output_name.c_str(), std::ios_base::out | std::ios_base::trunc);

    // terminate program if .asm file is not open.
    if (!file_data.is_open()) {
        std::cout << "There was an error when opening the specified file. Please try again." << std::endl;
        return 0;
    }

    // terminate program if .hack file is not open.
    if (!file_output.is_open()) {
        std::cout << "There was an error when opening the file. Please try again." << std::endl;
        return 0;
    }

    try {
        first_pass(file_data); 
        second_pass(file_data, file_output);
    } catch (const char* err) {
        std::cout << "ERROR at line number " << CURRENT_LINE+1 << ": " << err << std::endl;
        return 0;
    }

    std::cout << "Process completed successfully. .hack file has been generated." << std::endl;

    // closing the .asm file
    file_data.close();

    // closing the .hack file
    file_output.close();

    return 0;
}

void first_pass(std::istream & file_data) {
    std::string line = "";

    while (!file_data.eof()) {
        // ignore if next character is \n
        if (file_data.peek() == '\n') file_data.ignore();

        // read line
        std::getline(file_data, line);

        // Strip all whitespace from line
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // check if line should be ignored
        if (!helper::checkValid(line)) continue;

        // remove inline comments
        line = helper::removeInlineComment(line);

        // Authenticate the line and throw an exception if otherwise
        // handle labels as well
        if (!authenticator::instruction(line)) {
            throw ("An error occured.");
        }

        CURRENT_LINE++;
    }

    // populate variable map
    for (std::map<std::string, int>::iterator itr = symbols::labels.end(); itr != symbols::labels.begin(); itr--) {
        if (itr->second != -1) continue;

        symbols::variables[itr->first] = symbols::CURRENT_VARIABLE_ADDRESS;

        symbols::CURRENT_VARIABLE_ADDRESS++;
    }

}

void second_pass(std::istream & file_data, std::ostream & file_output) {
    std::string line = "";

    // resetting line counter
    CURRENT_LINE = 0;

    // reset the seekg position to 0
    file_data.clear();
    file_data.seekg(0);

    while (!file_data.eof()) {
        // ignore if next character is \n
        if (file_data.peek() == '\n') file_data.ignore();

        // read line
        std::getline(file_data, line);

        // Strip all whitespace from line
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // check if line should be ignored
        if (!helper::checkValid(line)) continue;

        // remove inline comments
        line = helper::removeInlineComment(line);

        // convert the instruction to binary and print to file and console
        if (parser::instruction(line) != "") {
            file_output << parser::instruction(line) << std::endl;
            std::cout << parser::instruction(line) << std::endl;
        }

        CURRENT_LINE++;
    }
}