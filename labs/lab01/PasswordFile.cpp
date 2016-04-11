// PasswordFile.cpp implementation file

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PasswordFile.h"

// Constructor
PasswordFile::PasswordFile(std::string filename) {
    std::ifstream infile(filename.c_str());
    std::string line, temp1, temp2;
    int counter = 0;
    while (std::getline(infile, line)) {
        std::istringstream word(line);
        word >> temp1 >> temp2;
        user.push_back(temp1);
        password.push_back(temp2);
    }
    infile.close();
}

void PasswordFile::addpw(std::string newUser, std::string newPassword) {

}

bool PasswordFile::checkpw(std::string usr, std::string pwd) {
    auto iter = std::find(user.begin(), user.end(), usr);
    if (iter == user.end()) {
        // not in vector
        return false;
    } else {
        int index = std::distance(user.begin(), iter);
        if (password[index] == pwd) {
            return true;
        }
        return false;
    }
}

int PasswordFile::salt = 1;

void PasswordFile::newsalt(int ns) {
    salt = ns;
}

std::string PasswordFile::encrypt(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] += salt;
    }
    return s;
}

std::string PasswordFile::decrypt(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] -= salt;
    }
    return s;
}

