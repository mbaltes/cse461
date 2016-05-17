// Name: Mark Baltes
// ID:   004899202
// File: Shell.cpp
//
// Shell class implementation.

#include "Shell.h"
#include <iostream>
#include <vector>

Shell::Shell(std::string diskName, int numberOfBlocks, int blockSize)
    : Filesys(diskName, numberOfBlocks, blockSize) {
    this->blockSize = blockSize;
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
    std::string buffer;
    char x;
    std::cout << "Input file contents (~ to end): " << '\n';
    std::cin.get(x);
    while (x != '~') {
        buffer += x;
        std::cin.get(x);
    }
    newFile(file);
    std::vector<std::string> blocked = block(buffer, this->blockSize);
    for (int i = 0; i < blocked.size(); i++) {
        addBlock(file, blocked[i]);
    }
}

// Deletes the file.
int Shell::del(std::string file) {
    while (getFirstBlock(file) > 0) {
        delBlock(file, getFirstBlock(file));
    }
    // File is empty, so able to delete.
    rmFile(file);
}

// Lists the contents of the file.
int Shell::type(std::string file) {
    std::string temp1;
    std::string temp2;
    int next = getFirstBlock(file);
    readBlock(file, next, temp1);
    int last = nextBlock(file, next);
    while (last != 0) {
        readBlock(file, last, temp2);
        temp1 += temp2;
        last = nextBlock(file, last);
    }
    std::cout << temp1 << '\n';
}

// Copies file1 to file2.
int Shell::copy(std::string file1, std::string file2) {
    int block = getFirstBlock(file1);
    if (block == -1) {
        std::cout << "No such file to copy." << '\n';
        return -1;
    } else if (getFirstBlock(file2) > 0) {
        std::cout << "Cannot overwrite file." << "\n";
        return -1;
    }
    newFile(file2);
    while (block != 0) {
        std::string buffer;
        readBlock(file1, block, buffer);
        addBlock(file2, buffer);
        block = nextBlock(file1, block);
    }
    return 1;
} 

void Shell::shellTest() {
    test();
}