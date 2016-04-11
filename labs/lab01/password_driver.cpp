// 

#include <iostream>
#include "PasswordFile.h"


int main() {
    //PasswordFile* x = new PasswordFile("password.txt");
    PasswordFile x("password.txt");
    std::cout << x.checkpw("riker", "smooth") << std::endl;
    std::cout << x.checkpw("riker", "heya") << std::endl;
}