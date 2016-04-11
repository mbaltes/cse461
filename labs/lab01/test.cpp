// test file

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream infile("password.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream word(line);
        std::string temp1, temp2;
        word >> temp1 >> temp2;
        std::cout << temp1 << " + " << temp2 << std::endl;
    }
}