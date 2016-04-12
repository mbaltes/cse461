/*
    @author: Mark Baltes
    @file: password_driver.cpp

    Test file for PasswordFile class.

*/

#include <iostream>
#include "PasswordFile.h"


int main() {
    PasswordFile x("password.txt");
    // Adding some users and checking their passwords.
    x.addpw("luke", "skyw");
    x.addpw("vadar", "mask");
    x.addpw("kylo", "crossaber");
    x.addpw("kylo", "again"); // Will fail. User already exists.
    if (x.checkpw("luke", "skyw")) {
        std::cout << "Password Correct" << std::endl;
    } else {
        std::cout << "Password incorrect." << std::endl;
    }
    if (x.checkpw("luke", "nope")) {
        std::cout << "Password Correct" << std::endl;
    } else {
        std::cout << "Password Incorrect." << std::endl;
    }
    if (x.checkpw("vadar", "mask")) {
        std::cout << "Password Correct" << std::endl;
    } else {
        std::cout << "Password incorrect." << std::endl;
    }
}