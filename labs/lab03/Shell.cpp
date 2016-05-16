// Name: Mark Baltes
// ID:   004899202
// File: Shell.cpp
//
// Shell class implementation.

#include "Shell.h"

Shell::Shell(std::string diskName, int numberOfBlocks, int blockSize)
    : Filesys(diskName, numberOfBlocks, blockSize) {
    std::cout << "Shell created." << '\n';
}

// Lists all files.
int Shell::dir() {
    std::vector<std::string> flist = ls();
    for (int i = 0; i < flist.size(); i++) {
        std::cout << flist[i] << std::endl;
    }
}

// Adds a new file using input from keyboard.
int Shell::add(std::string file) {
    newFile(file);
}

// Deletes the file.
int del(std::string file) {
    rmFile(file);
}

// Lists the contents of the file.
int type(std::string file) {
    //
}

// Copies file1 to file2.
int copy(std::string file1, std::string file2) {
    //
}