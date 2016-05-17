//
//
#include <iostream>
#include <string>
#include "Shell.h"

int main() {
    //
    //This main program inputs commands to the shell.
    //It inputs commands as : command op1 op2
    //You should modify it to work for your implementation.
    //

    Shell sh("disk5", 16, 32);

    std::string s;
    std::string command = "go";
    std::string op1, op2;

    while (command != "quit") {
        // Testing
        //sh.test();
        command.clear();
        op1.clear();
        op2.clear();
        std::cout << "$ ";
        std::getline(std::cin, s);
        int firstblank=s.find(' ');
        if (firstblank < s.length()) s[firstblank]='#';
        int secondblank=s.find(' ');
        command=s.substr(0,firstblank);
        if (firstblank < s.length())
        op1=s.substr(firstblank+1,secondblank-firstblank-1);
        if (secondblank < s.length())
        op2=s.substr(secondblank+1);
        if (command == "dir") {
            // use the ls function
            sh.dir();
        }
        if (command == "add") {
            // The variable op1 is the new file
            sh.add(op1);
        }
        if (command == "del") {
            // The variable op1 is the file
            sh.del(op1);
        }
        if (command == "type") {
            // The variable op1 is the file
            sh.type(op1);
        }
        if (command == "copy") {
            // The variable op1 is the source file and the variable op2 is the 
            // destination file.
            sh.copy(op1, op2);
        }
    }
    return 0;
}