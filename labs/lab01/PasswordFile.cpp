// PasswordFile.cpp implementation file

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PasswordFile.h"

// Constructor
PasswordFile::PasswordFile(std::string filename) {
    this->filename = filename;
    std::ifstream infile(filename.c_str());
    std::string line, temp1, temp2;
    int counter = 0;
    while (std::getline(infile, line)) {
        std::istringstream word(line);
        word >> temp1 >> temp2;
        user.push_back(temp1);
        password.push_back(encrypt(temp2));
    }
    infile.close();
}

void PasswordFile::addpw(std::string newUser, std::string newPassword) {
    // Verify user doesn't exist, then add.
    auto iter = std::find(user.begin(), user.end(), newUser);
    if (iter == user.end()) {
        // User not found. OK to add.
        user.push_back(newUser);
        password.push_back(encrypt(newPassword));
        synch();
    } else {
        // User already exits.
        std::cout << "Cannot add. User " << newUser << " already exists." << std::endl;
    }
    
}

bool PasswordFile::checkpw(std::string usr, std::string pwd) {
    std::string encryptedPwd = encrypt(pwd);
    auto iter = std::find(user.begin(), user.end(), usr);
    if (iter == user.end()) {
        // not in vector
        return false;
    } else {
        int index = std::distance(user.begin(), iter);
        if (password[index] == encryptedPwd) {
            return true;
        }
        return false;
    }
}

void PasswordFile::synch() {
    std::ofstream outfile(this->filename);
    for (int i = 0; i < user.size(); i++) {
        outfile << user[i] << " " << decrypt(password[i]) << std::endl;
    }
    outfile.close();
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

