// Name: Mark Baltes
// ID:   004899202
// File: Shell.h
//
// Shell class description.

#ifndef SHELL_H
#define SHELL_H

#include <string>
#include "Filesys.h"

class Shell : public Filesys {
public:
    Shell(std::string diskName, int numberOfBlocks, int blockSize);
    int dir(); // Lists all files.
    int add(std::string file); // Adds a new file using input from keyboard.
    int del(std::string file); // Deletes the file.
    int type(std::string file); // Lists the contents of the file.
    int copy(std::string file1, std::string file2); // Copies file1 to file2.
    void shellTest();
private:
    int blockSize;
};

#endif