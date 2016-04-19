// Name: Mark Baltes
// ID:   004899202
// File: Sdisk.cpp
//
// Implementation for Sdisk class.

#include "Sdisk.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Constructor
Sdisk::Sdisk(std::string diskName, int numberOfBlocks, int blockSize) {
    std::ifstream iofile(diskName.c_str(), std::ios::in | std::ios::out);
    if (!iofile) {  // File doesn't exist, so build new disk.
        std::ofstream outfile(diskName.c_str(), std::ios::out);
        for (int i = 0; i < numberOfBlocks * blockSize; i++) {
            outfile << "#";
        }
        this->diskName = diskName;
        this->numberOfBlocks = numberOfBlocks;
        this->blockSize = blockSize;
        iofile.close();
        outfile.close();
    } else {
        this->diskName = diskName;
        this->numberOfBlocks = numberOfBlocks;
        this->blockSize = blockSize;
        iofile.close();
    }
}

int Sdisk::getBlock(int blockNumber, std::string& buffer) {
    if (blockNumber < 0 || blockNumber > numberOfBlocks) {
        throw std::invalid_argument("ERROR: Block out of bounds.");
        return 0;
    }
    std::fstream iofile(diskName.c_str(), std::ios::in | std::ios::out);
    int position = blockNumber * blockSize;
    int counter = 1;
    iofile.seekg(position);
    char temp;
    iofile.get(temp);
    while (iofile.good() and counter <= blockSize) {
        buffer += temp;
        iofile.get(temp);
        counter++; 
    }
    iofile.close();
    return 1;
}

int Sdisk::putBlock(int blockNumber, std::string buffer) {
    if (blockNumber < 0 || blockNumber > numberOfBlocks) {
        throw std::invalid_argument("ERROR: Block out of bounds.");
        return 0;
    } else if (buffer.size() > blockSize) {
        throw std::invalid_argument("ERROR: Block too big, cannot write.");
        return 0;
    } else {
        std::fstream iofile(diskName.c_str(), std::ios::in | std::ios::out);
        int position = blockNumber * blockSize;
        iofile.seekp(position);
        iofile << buffer;
        iofile.close();
    }
    return 1;
}

int Sdisk::getNumberOfBlocks() {
    return numberOfBlocks;
}

int Sdisk::getBlocksize() {
    return blockSize;
}
